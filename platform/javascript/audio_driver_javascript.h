
/*  audio_driver_javascript.h                                            */

#ifndef AUDIO_DRIVER_JAVASCRIPT_H
#define AUDIO_DRIVER_JAVASCRIPT_H

#include "servers/audio_server.h"

class AudioDriverJavaScript : public AudioDriver {
	float *internal_buffer = nullptr;

	int _driver_id = 0;
	int buffer_length = 0;

public:
	static bool is_available();
	void mix_to_js();
	void process_capture(float sample);

	static AudioDriverJavaScript *singleton;

	virtual const char *get_name() const;

	virtual Error init();
	virtual void start();
	void resume();
	virtual float get_latency();
	virtual int get_mix_rate() const;
	virtual SpeakerMode get_speaker_mode() const;
	virtual void lock();
	virtual void unlock();
	virtual void finish();
	void finish_async();

	virtual Error capture_start();
	virtual Error capture_stop();

	AudioDriverJavaScript();
};

#endif
