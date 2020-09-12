
/*  audio_driver_jandroid.h                                              */

#ifndef AUDIO_DRIVER_ANDROID_H
#define AUDIO_DRIVER_ANDROID_H

#include "servers/audio_server.h"

#include "java_godot_lib_jni.h"

class AudioDriverAndroid : public AudioDriver {
	static Mutex mutex;
	static AudioDriverAndroid *s_ad;
	static jobject io;
	static jmethodID _init_audio;
	static jmethodID _write_buffer;
	static jmethodID _quit;
	static jmethodID _pause;
	static bool active;
	static bool quit;

	static jclass cls;

	static jobject audioBuffer;
	static void *audioBufferPinned;
	static int32_t *audioBuffer32;
	static int audioBufferFrames;
	static int mix_rate;

public:
	void set_singleton();

	virtual const char *get_name() const;

	virtual Error init();
	virtual void start();
	virtual int get_mix_rate() const;
	virtual SpeakerMode get_speaker_mode() const;
	virtual void lock();
	virtual void unlock();
	virtual void finish();

	virtual void set_pause(bool p_pause);

	static void setup(jobject p_io);
	static void thread_func(JNIEnv *env);

	AudioDriverAndroid();
};

#endif // AUDIO_DRIVER_ANDROID_H
