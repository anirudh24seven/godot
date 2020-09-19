
/*  texture_basisu.h                                                     */

#ifndef BASIS_UNIVERSAL_TEXTURE_BASISU_H
#define BASIS_UNIVERSAL_TEXTURE_BASISU_H

#include "scene/resources/texture.h"

#ifdef TOOLS_ENABLED
#include <basisu_comp.h>
#endif

#include <transcoder/basisu_transcoder.h>

#if 0
class TextureBasisU : public Texture {

	GDCLASS(TextureBasisU, Texture);
	RES_BASE_EXTENSION("butex");

	RID texture;
	Size2 tex_size;

	uint32_t flags;

	Vector<uint8_t> data;

	static void _bind_methods();

public:

	virtual int get_width() const;
	virtual int get_height() const;
	virtual RID get_rid() const;
	virtual bool has_alpha() const;

	virtual void set_flags(uint32_t p_flags);
	virtual uint32_t get_flags() const;

Error import(const Ref<Image> &p_img);

	void set_basisu_data(const Vector<uint8_t>& p_data);

	Vector<uint8_t> get_basisu_data() const;
	String get_img_path() const;

	TextureBasisU();
	~TextureBasisU();

};

#endif

#endif // BASIS_UNIVERSAL_TEXTURE_BASISU_H
