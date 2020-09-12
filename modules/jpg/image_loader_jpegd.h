
/*  image_loader_jpegd.h                                                 */

#ifndef IMAGE_LOADER_JPG_H
#define IMAGE_LOADER_JPG_H

#include "core/io/image_loader.h"

class ImageLoaderJPG : public ImageFormatLoader {
public:
	virtual Error load_image(Ref<Image> p_image, FileAccess *f, bool p_force_linear, float p_scale);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	ImageLoaderJPG();
};

#endif
