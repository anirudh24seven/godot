
/*  audio_driver_dummy.h                                                 */

#ifndef AUDIO_DRIVER_DUMMY_H
#define AUDIO_DRIVER_DUMMY_H

#include "servers/audio_server.h"

#include "core/os/mutex.h"
#include "core/os/thread.h"

class AudioDriverDummy : public AudioDriver {
	Thread *thread = nullptr;
	Mutex mutex;

	int32_t *samples_in;

	static void thread_func(void *p_udata);

	unsigned int buffer_frames;
	unsigned int mix_rate;
	SpeakerMode speaker_mode;

	int channels;

	bool active;
	bool thread_exited;
	mutable bool exit_thread;

public:
	const char *get_name() const {
		return "Dummy";
	};

	virtual Error init();
	virtual void start();
	virtual int get_mix_rate() const;
	virtual SpeakerMode get_speaker_mode() const;
	virtual void lock();
	virtual void unlock();
	virtual void finish();

	AudioDriverDummy() {}
	~AudioDriverDummy() {}
};

#endif
