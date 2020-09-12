
/*  register_types.cpp                                                   */

#include "register_types.h"

#include "image_loader_bmp.h"

static ImageLoaderBMP *image_loader_bmp = nullptr;

void register_bmp_types() {
	image_loader_bmp = memnew(ImageLoaderBMP);
	ImageLoader::add_image_format_loader(image_loader_bmp);
}

void unregister_bmp_types() {
	memdelete(image_loader_bmp);
}
