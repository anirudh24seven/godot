
/*  register_types.cpp                                                   */



#include "register_types.h"

#include "image_loader_webp.h"

static ImageLoaderWEBP *image_loader_webp = nullptr;

void register_webp_types() {
	image_loader_webp = memnew(ImageLoaderWEBP);
	ImageLoader::add_image_format_loader(image_loader_webp);
}

void unregister_webp_types() {
	memdelete(image_loader_webp);
}
