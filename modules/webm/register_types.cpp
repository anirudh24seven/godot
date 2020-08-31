
/*  register_types.cpp                                                   */



#include "register_types.h"

#include "video_stream_webm.h"

static Ref<ResourceFormatLoaderWebm> resource_loader_webm;

void register_webm_types() {
	resource_loader_webm.instance();
	ResourceLoader::add_resource_format_loader(resource_loader_webm, true);

	ClassDB::register_class<VideoStreamWebm>();
}

void unregister_webm_types() {
	ResourceLoader::remove_resource_format_loader(resource_loader_webm);
	resource_loader_webm.unref();
}
