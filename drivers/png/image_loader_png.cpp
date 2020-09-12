
/*  image_loader_png.cpp                                                 */

#include "image_loader_png.h"

#include "core/os/os.h"
#include "core/print_string.h"
#include "drivers/png/png_driver_common.h"

#include <string.h>

Error ImageLoaderPNG::load_image(Ref<Image> p_image, FileAccess *f, bool p_force_linear, float p_scale) {
	const size_t buffer_size = f->get_len();
	Vector<uint8_t> file_buffer;
	Error err = file_buffer.resize(buffer_size);
	if (err) {
		f->close();
		return err;
	}
	{
		uint8_t *writer = file_buffer.ptrw();
		f->get_buffer(writer, buffer_size);
		f->close();
	}
	const uint8_t *reader = file_buffer.ptr();
	return PNGDriverCommon::png_to_image(reader, buffer_size, p_force_linear, p_image);
}

void ImageLoaderPNG::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("png");
}

Ref<Image> ImageLoaderPNG::load_mem_png(const uint8_t *p_png, int p_size) {
	Ref<Image> img;
	img.instance();

	// the value of p_force_linear does not matter since it only applies to 16 bit
	Error err = PNGDriverCommon::png_to_image(p_png, p_size, false, img);
	ERR_FAIL_COND_V(err, Ref<Image>());

	return img;
}

Ref<Image> ImageLoaderPNG::lossless_unpack_png(const Vector<uint8_t> &p_data) {
	const int len = p_data.size();
	ERR_FAIL_COND_V(len < 4, Ref<Image>());
	const uint8_t *r = p_data.ptr();
	ERR_FAIL_COND_V(r[0] != 'P' || r[1] != 'N' || r[2] != 'G' || r[3] != ' ', Ref<Image>());
	return load_mem_png(&r[4], len - 4);
}

Vector<uint8_t> ImageLoaderPNG::lossless_pack_png(const Ref<Image> &p_image) {
	Vector<uint8_t> out_buffer;

	// add Godot's own "PNG " prefix
	if (out_buffer.resize(4) != OK) {
		ERR_FAIL_V(Vector<uint8_t>());
	}

	// scope for writer lifetime
	{
		// must be closed before call to image_to_png
		uint8_t *writer = out_buffer.ptrw();
		copymem(writer, "PNG ", 4);
	}

	Error err = PNGDriverCommon::image_to_png(p_image, out_buffer);
	if (err) {
		ERR_FAIL_V(Vector<uint8_t>());
	}

	return out_buffer;
}

ImageLoaderPNG::ImageLoaderPNG() {
	Image::_png_mem_loader_func = load_mem_png;
	Image::lossless_unpacker = lossless_unpack_png;
	Image::lossless_packer = lossless_pack_png;
}
