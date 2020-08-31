
/*  audio_driver_coreaudio.h                                             */



#ifdef COREAUDIO_ENABLED

#ifndef AUDIO_DRIVER_COREAUDIO_H
#define AUDIO_DRIVER_COREAUDIO_H

#include "servers/audio_server.h"

#include <AudioUnit/AudioUnit.h>
#ifdef OSX_ENABLED
#include <CoreAudio/AudioHardware.h>
#endif

class AudioDriverCoreAudio : public AudioDriver {
	AudioComponentInstance audio_unit = nullptr;
	AudioComponentInstance input_unit = nullptr;

	bool active = false;
	Mutex mutex;

	String device_name = "Default";
	String capture_device_name = "Default";

	int mix_rate = 0;
	unsigned int channels = 2;
	unsigned int capture_channels = 2;
	unsigned int buffer_frames = 0;

	Vector<int32_t> samples_in;
	Vector<int16_t> input_buf;

#ifdef OSX_ENABLED
	Array _get_device_list(bool capture = false);
	void _set_device(const String &device, bool capture = false);

	static OSStatus input_device_address_cb(AudioObjectID inObjectID,
			UInt32 inNumberAddresses, const AudioObjectPropertyAddress *inAddresses,
			void *inClientData);

	static OSStatus output_device_address_cb(AudioObjectID inObjectID,
			UInt32 inNumberAddresses, const AudioObjectPropertyAddress *inAddresses,
			void *inClientData);
#endif

	static OSStatus output_callback(void *inRefCon,
			AudioUnitRenderActionFlags *ioActionFlags,
			const AudioTimeStamp *inTimeStamp,
			UInt32 inBusNumber, UInt32 inNumberFrames,
			AudioBufferList *ioData);

	static OSStatus input_callback(void *inRefCon,
			AudioUnitRenderActionFlags *ioActionFlags,
			const AudioTimeStamp *inTimeStamp,
			UInt32 inBusNumber, UInt32 inNumberFrames,
			AudioBufferList *ioData);

	Error capture_init();
	void capture_finish();

public:
	const char *get_name() const {
		return "CoreAudio";
	};

	virtual Error init();
	virtual void start();
	virtual int get_mix_rate() const;
	virtual SpeakerMode get_speaker_mode() const;

	virtual void lock();
	virtual void unlock();
	virtual void finish();

	virtual Error capture_start();
	virtual Error capture_stop();

	bool try_lock();
	void stop();

#ifdef OSX_ENABLED
	virtual Array get_device_list();
	virtual String get_device();
	virtual void set_device(String device);

	virtual Array capture_get_device_list();
	virtual void capture_set_device(const String &p_name);
	virtual String capture_get_device();
#endif

	AudioDriverCoreAudio();
	~AudioDriverCoreAudio() {}
};

#endif

#endif
