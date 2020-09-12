
/*  reverb.h                                                             */

// Author: Juan Linietsky <reduzio@gmail.com>, (C) 2006

#ifndef REVERB_H
#define REVERB_H

#include "core/math/audio_frame.h"
#include "core/os/memory.h"
#include "core/typedefs.h"

class Reverb {
public:
	enum {
		INPUT_BUFFER_MAX_SIZE = 1024,

	};

private:
	enum {

		MAX_COMBS = 8,
		MAX_ALLPASS = 4,
		MAX_ECHO_MS = 500

	};

	static const float comb_tunings[MAX_COMBS];
	static const float allpass_tunings[MAX_ALLPASS];

	struct Comb {
		int size = 0;
		float *buffer = nullptr;
		float feedback = 0;
		float damp = 0; //lowpass
		float damp_h = 0; //history
		int pos = 0;
		int extra_spread_frames = 0;

		Comb() {}
	};

	struct AllPass {
		int size = 0;
		float *buffer = nullptr;
		int pos = 0;
		int extra_spread_frames = 0;
		AllPass() {}
	};

	Comb comb[MAX_COMBS];
	AllPass allpass[MAX_ALLPASS];
	float *input_buffer;
	float *echo_buffer = nullptr;
	int echo_buffer_size;
	int echo_buffer_pos;

	float hpf_h1, hpf_h2 = 0;

	struct Parameters {
		float room_size;
		float damp;
		float wet;
		float dry;
		float mix_rate;
		float extra_spread_base;
		float extra_spread;
		float predelay;
		float predelay_fb;
		float hpf;
	} params;

	void configure_buffers();
	void update_parameters();
	void clear_buffers();

public:
	void set_room_size(float p_size);
	void set_damp(float p_damp);
	void set_wet(float p_wet);
	void set_dry(float p_dry);
	void set_predelay(float p_predelay); // in ms
	void set_predelay_feedback(float p_predelay_fb); // in ms
	void set_highpass(float p_frq);
	void set_mix_rate(float p_mix_rate);
	void set_extra_spread(float p_spread);
	void set_extra_spread_base(float p_sec);

	void process(float *p_src, float *p_dst, int p_frames);

	Reverb();

	~Reverb();
};

#endif
