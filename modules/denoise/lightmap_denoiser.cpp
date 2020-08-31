
/*  lightmap_denoiser.cpp                                                */



#include "lightmap_denoiser.h"
#include "denoise_wrapper.h"

LightmapDenoiser *LightmapDenoiserOIDN::create_oidn_denoiser() {
	return memnew(LightmapDenoiserOIDN);
}

void LightmapDenoiserOIDN::make_default_denoiser() {
	create_function = create_oidn_denoiser;
}

Ref<Image> LightmapDenoiserOIDN::denoise_image(const Ref<Image> &p_image) {
	Ref<Image> img = p_image->duplicate();

	img->convert(Image::FORMAT_RGBF);

	Vector<uint8_t> data = img->get_data();
	if (!oidn_denoise(device, (float *)data.ptrw(), img->get_width(), img->get_height())) {
		return p_image;
	}

	img->create(img->get_width(), img->get_height(), false, img->get_format(), data);
	return img;
}

LightmapDenoiserOIDN::LightmapDenoiserOIDN() {
	device = oidn_denoiser_init();
}

LightmapDenoiserOIDN::~LightmapDenoiserOIDN() {
	oidn_denoiser_finish(device);
}
