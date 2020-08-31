
/*  audio_effect_panner.h                                                */



#ifndef AUDIOEFFECTPANNER_H
#define AUDIOEFFECTPANNER_H

#include "servers/audio/audio_effect.h"

class AudioEffectPanner;

class AudioEffectPannerInstance : public AudioEffectInstance {
	GDCLASS(AudioEffectPannerInstance, AudioEffectInstance);
	friend class AudioEffectPanner;
	Ref<AudioEffectPanner> base;

public:
	virtual void process(const AudioFrame *p_src_frames, AudioFrame *p_dst_frames, int p_frame_count) override;
};

class AudioEffectPanner : public AudioEffect {
	GDCLASS(AudioEffectPanner, AudioEffect);

	friend class AudioEffectPannerInstance;
	float pan;

protected:
	static void _bind_methods();

public:
	Ref<AudioEffectInstance> instance() override;
	void set_pan(float p_cpanume);
	float get_pan() const;

	AudioEffectPanner();
};

#endif // AUDIOEFFECTPANNER_H
