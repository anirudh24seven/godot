
/*  audio_driver_jandroid.cpp                                            */

#include "audio_driver_jandroid.h"

#include "core/os/os.h"
#include "core/project_settings.h"
#include "thread_jandroid.h"

AudioDriverAndroid *AudioDriverAndroid::s_ad = nullptr;

jobject AudioDriverAndroid::io;
jmethodID AudioDriverAndroid::_init_audio;
jmethodID AudioDriverAndroid::_write_buffer;
jmethodID AudioDriverAndroid::_quit;
jmethodID AudioDriverAndroid::_pause;
bool AudioDriverAndroid::active = false;
jclass AudioDriverAndroid::cls;
int AudioDriverAndroid::audioBufferFrames = 0;
int AudioDriverAndroid::mix_rate = 44100;
bool AudioDriverAndroid::quit = false;
jobject AudioDriverAndroid::audioBuffer = nullptr;
void *AudioDriverAndroid::audioBufferPinned = nullptr;
Mutex AudioDriverAndroid::mutex;
int32_t *AudioDriverAndroid::audioBuffer32 = nullptr;

const char *AudioDriverAndroid::get_name() const {
	return "Android";
}

Error AudioDriverAndroid::init() {
	/*
	// TODO: pass in/return a (Java) device ID, also whether we're opening for input or output
	   this->spec.samples = Android_JNI_OpenAudioDevice(this->spec.freq, this->spec.format == AUDIO_U8 ? 0 : 1, this->spec.channels, this->spec.samples);
	   SDL_CalculateAudioSpec(&this->spec);

	   if (this->spec.samples == 0) {
	       // Init failed?
	       SDL_SetError("Java-side initialization failed!");
	       return 0;
	   }
*/

	//Android_JNI_SetupThread();

	//        __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL audio: opening device");

	JNIEnv *env = ThreadAndroid::get_env();
	int mix_rate = GLOBAL_GET("audio/mix_rate");

	int latency = GLOBAL_GET("audio/output_latency");
	unsigned int buffer_size = next_power_of_2(latency * mix_rate / 1000);
	print_verbose("Audio buffer size: " + itos(buffer_size));

	audioBuffer = env->CallObjectMethod(io, _init_audio, mix_rate, buffer_size);

	ERR_FAIL_COND_V(audioBuffer == nullptr, ERR_INVALID_PARAMETER);

	audioBuffer = env->NewGlobalRef(audioBuffer);

	jboolean isCopy = JNI_FALSE;
	audioBufferPinned = env->GetShortArrayElements((jshortArray)audioBuffer, &isCopy);
	audioBufferFrames = env->GetArrayLength((jshortArray)audioBuffer);
	audioBuffer32 = memnew_arr(int32_t, audioBufferFrames);

	return OK;
}

void AudioDriverAndroid::start() {
	active = true;
}

void AudioDriverAndroid::setup(jobject p_io) {
	JNIEnv *env = ThreadAndroid::get_env();
	io = p_io;

	jclass c = env->GetObjectClass(io);
	cls = (jclass)env->NewGlobalRef(c);

	_init_audio = env->GetMethodID(cls, "audioInit", "(II)Ljava/lang/Object;");
	_write_buffer = env->GetMethodID(cls, "audioWriteShortBuffer", "([S)V");
	_quit = env->GetMethodID(cls, "audioQuit", "()V");
	_pause = env->GetMethodID(cls, "audioPause", "(Z)V");
}

void AudioDriverAndroid::thread_func(JNIEnv *env) {
	jclass cls = env->FindClass("org/godotengine/godot/Godot");
	if (cls) {
		cls = (jclass)env->NewGlobalRef(cls);
	}
	jfieldID fid = env->GetStaticFieldID(cls, "io", "Lorg/godotengine/godot/GodotIO;");
	jobject ob = env->GetStaticObjectField(cls, fid);
	jobject gob = env->NewGlobalRef(ob);
	jclass c = env->GetObjectClass(gob);
	jclass lcls = (jclass)env->NewGlobalRef(c);
	_write_buffer = env->GetMethodID(lcls, "audioWriteShortBuffer", "([S)V");

	while (!quit) {
		int16_t *ptr = (int16_t *)audioBufferPinned;
		int fc = audioBufferFrames;

		if (!s_ad->active || mutex.try_lock() != OK) {
			for (int i = 0; i < fc; i++) {
				ptr[i] = 0;
			}

		} else {
			s_ad->audio_server_process(fc / 2, audioBuffer32);

			mutex.unlock();

			for (int i = 0; i < fc; i++) {
				ptr[i] = audioBuffer32[i] >> 16;
			}
		}
		env->ReleaseShortArrayElements((jshortArray)audioBuffer, (jshort *)ptr, JNI_COMMIT);
		env->CallVoidMethod(gob, _write_buffer, (jshortArray)audioBuffer);
	}
}

int AudioDriverAndroid::get_mix_rate() const {
	return mix_rate;
}

AudioDriver::SpeakerMode AudioDriverAndroid::get_speaker_mode() const {
	return SPEAKER_MODE_STEREO;
}

void AudioDriverAndroid::lock() {
	mutex.lock();
}

void AudioDriverAndroid::unlock() {
	mutex.unlock();
}

void AudioDriverAndroid::finish() {
	JNIEnv *env = ThreadAndroid::get_env();
	env->CallVoidMethod(io, _quit);

	if (audioBuffer) {
		env->DeleteGlobalRef(audioBuffer);
		audioBuffer = nullptr;
		audioBufferPinned = nullptr;
	}

	active = false;
}

void AudioDriverAndroid::set_pause(bool p_pause) {
	JNIEnv *env = ThreadAndroid::get_env();
	env->CallVoidMethod(io, _pause, p_pause);
}

AudioDriverAndroid::AudioDriverAndroid() {
	s_ad = this;
	active = false;
}
