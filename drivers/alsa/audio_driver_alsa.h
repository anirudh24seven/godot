
/*  audio_driver_alsa.h                                                  */

#ifdef ALSA_ENABLED

#ifndef AUDIO_DRIVER_ALSA_H
#define AUDIO_DRIVER_ALSA_H

#include "core/os/mutex.h"
#include "core/os/thread.h"
#include "servers/audio_server.h"

#include <alsa/asoundlib.h>

class AudioDriverALSA : public AudioDriver {
	Thread *thread = nullptr;
	Mutex mutex;

	snd_pcm_t *pcm_handle = nullptr;

	String device_name = "Default";
	String new_device = "Default";

	Vector<int32_t> samples_in;
	Vector<int16_t> samples_out;

	Error init_device();
	void finish_device();

	static void thread_func(void *p_udata);

	unsigned int mix_rate;
	SpeakerMode speaker_mode;

	snd_pcm_uframes_t buffer_frames;
	snd_pcm_uframes_t buffer_size;
	snd_pcm_uframes_t period_size;
	int channels;

	bool active;
	bool thread_exited;
	mutable bool exit_thread;

public:
	const char *get_name() const {
		return "ALSA";
	};

	virtual Error init();
	virtual void start();
	virtual int get_mix_rate() const;
	virtual SpeakerMode get_speaker_mode() const;
	virtual Array get_device_list();
	virtual String get_device();
	virtual void set_device(String device);
	virtual void lock();
	virtual void unlock();
	virtual void finish();

	AudioDriverALSA() {}
	~AudioDriverALSA() {}
};

#endif // AUDIO_DRIVER_ALSA_H

#endif // ALSA_ENABLED
