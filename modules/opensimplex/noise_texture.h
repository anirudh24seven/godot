
/*  noise_texture.h                                                      */

#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "open_simplex_noise.h"

#include "core/image.h"
#include "core/reference.h"
#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "editor/property_editor.h"

class NoiseTexture : public Texture2D {
	GDCLASS(NoiseTexture, Texture2D);

private:
	Ref<Image> data;

	Thread *noise_thread;

	bool first_time;
	bool update_queued;
	bool regen_queued;

	mutable RID texture;
	uint32_t flags;

	Ref<OpenSimplexNoise> noise;
	Vector2i size;
	bool seamless;
	bool as_normalmap;
	float bump_strength;

	void _thread_done(const Ref<Image> &p_image);
	static void _thread_function(void *p_ud);

	void _queue_update();
	Ref<Image> _generate_texture();
	void _update_texture();
	void _set_texture_data(const Ref<Image> &p_image);

protected:
	static void _bind_methods();
	virtual void _validate_property(PropertyInfo &property) const override;

public:
	void set_noise(Ref<OpenSimplexNoise> p_noise);
	Ref<OpenSimplexNoise> get_noise();

	void set_width(int p_width);
	void set_height(int p_height);

	void set_seamless(bool p_seamless);
	bool get_seamless();

	void set_as_normalmap(bool p_as_normalmap);
	bool is_normalmap();

	void set_bump_strength(float p_bump_strength);
	float get_bump_strength();

	int get_width() const override;
	int get_height() const override;

	virtual RID get_rid() const override;
	virtual bool has_alpha() const override { return false; }

	virtual Ref<Image> get_data() const override;

	NoiseTexture();
	virtual ~NoiseTexture();
};

#endif // NOISE_TEXTURE_H
