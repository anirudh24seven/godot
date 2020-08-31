
/*  texture_loader_pkm.cpp                                               */



#include "texture_loader_pkm.h"

#include "core/os/file_access.h"
#include <string.h>

struct ETC1Header {
	char tag[6]; // "PKM 10"
	uint16_t format; // Format == number of mips (== zero)
	uint16_t texWidth; // Texture dimensions, multiple of 4 (big-endian)
	uint16_t texHeight;
	uint16_t origWidth; // Original dimensions (big-endian)
	uint16_t origHeight;
};

RES ResourceFormatPKM::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, bool p_no_cache) {
	if (r_error) {
		*r_error = ERR_CANT_OPEN;
	}

	Error err;
	FileAccess *f = FileAccess::open(p_path, FileAccess::READ, &err);
	if (!f) {
		return RES();
	}

	FileAccessRef fref(f);
	if (r_error) {
		*r_error = ERR_FILE_CORRUPT;
	}

	ERR_FAIL_COND_V_MSG(err != OK, RES(), "Unable to open PKM texture file '" + p_path + "'.");

	// big endian
	f->set_endian_swap(true);

	ETC1Header h;
	f->get_buffer((uint8_t *)&h.tag, sizeof(h.tag));
	ERR_FAIL_COND_V_MSG(strncmp(h.tag, "PKM 10", sizeof(h.tag)), RES(), "Invalid or unsupported PKM texture file '" + p_path + "'.");

	h.format = f->get_16();
	h.texWidth = f->get_16();
	h.texHeight = f->get_16();
	h.origWidth = f->get_16();
	h.origHeight = f->get_16();

	Vector<uint8_t> src_data;

	uint32_t size = h.texWidth * h.texHeight / 2;
	src_data.resize(size);
	uint8_t *wb = src_data.ptrw();
	f->get_buffer(wb, size);

	int mipmaps = h.format;
	int width = h.origWidth;
	int height = h.origHeight;

	Ref<Image> img = memnew(Image(width, height, mipmaps, Image::FORMAT_ETC, src_data));

	Ref<ImageTexture> texture = memnew(ImageTexture);
	texture->create_from_image(img);

	if (r_error) {
		*r_error = OK;
	}

	f->close();
	memdelete(f);
	return texture;
}

void ResourceFormatPKM::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("pkm");
}

bool ResourceFormatPKM::handles_type(const String &p_type) const {
	return ClassDB::is_parent_class(p_type, "Texture2D");
}

String ResourceFormatPKM::get_resource_type(const String &p_path) const {
	if (p_path.get_extension().to_lower() == "pkm") {
		return "ImageTexture";
	}
	return "";
}
