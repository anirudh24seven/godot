
/*  texture_loader_dummy.cpp                                             */

#include "texture_loader_dummy.h"

#include "core/os/file_access.h"
#include "core/print_string.h"

#include <string.h>

RES ResourceFormatDummyTexture::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, bool p_no_cache) {
	unsigned int width = 8;
	unsigned int height = 8;

	//We just use some format
	Image::Format fmt = Image::FORMAT_RGB8;
	int rowsize = 3 * width;

	Vector<uint8_t> dstbuff;

	dstbuff.resize(rowsize * height);

	uint8_t **row_p = memnew_arr(uint8_t *, height);

	for (unsigned int i = 0; i < height; i++) {
		row_p[i] = 0; //No colors any more, I want them to turn black
	}

	memdelete_arr(row_p);

	Ref<Image> img = memnew(Image(width, height, 0, fmt, dstbuff));

	Ref<ImageTexture> texture = memnew(ImageTexture);
	texture->create_from_image(img);

	if (r_error)
		*r_error = OK;

	return texture;
}

void ResourceFormatDummyTexture::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("bmp");
	p_extensions->push_back("dds");
	p_extensions->push_back("exr");
	p_extensions->push_back("jpeg");
	p_extensions->push_back("jpg");
	p_extensions->push_back("hdr");
	p_extensions->push_back("pkm");
	p_extensions->push_back("png");
	p_extensions->push_back("pvr");
	p_extensions->push_back("svg");
	p_extensions->push_back("svgz");
	p_extensions->push_back("tga");
	p_extensions->push_back("webp");
}

bool ResourceFormatDummyTexture::handles_type(const String &p_type) const {
	return ClassDB::is_parent_class(p_type, "Texture2D");
}

String ResourceFormatDummyTexture::get_resource_type(const String &p_path) const {
	String extension = p_path.get_extension().to_lower();
	if (
			extension == "bmp" ||
			extension == "dds" ||
			extension == "exr" ||
			extension == "jpeg" ||
			extension == "jpg" ||
			extension == "hdr" ||
			extension == "pkm" ||
			extension == "png" ||
			extension == "pvr" ||
			extension == "svg" ||
			extension == "svgz" ||
			extension == "tga" ||
			extension == "webp") {
		return "ImageTexture";
	}

	return "";
}
