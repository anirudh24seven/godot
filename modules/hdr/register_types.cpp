
/*  register_types.cpp                                                   */



#include "register_types.h"

#include "image_loader_hdr.h"

static ImageLoaderHDR *image_loader_hdr = nullptr;

void register_hdr_types() {
	image_loader_hdr = memnew(ImageLoaderHDR);
	ImageLoader::add_image_format_loader(image_loader_hdr);
}

void unregister_hdr_types() {
	memdelete(image_loader_hdr);
}
