
/*  lightmap_denoiser.h                                                  */

#ifndef LIGHTMAP_DENOISER_H
#define LIGHTMAP_DENOISER_H

#include "core/object.h"
#include "scene/3d/lightmapper.h"

struct OIDNDeviceImpl;

class LightmapDenoiserOIDN : public LightmapDenoiser {
	GDCLASS(LightmapDenoiserOIDN, LightmapDenoiser);

protected:
	void *device = nullptr;

public:
	static LightmapDenoiser *create_oidn_denoiser();

	Ref<Image> denoise_image(const Ref<Image> &p_image) override;

	static void make_default_denoiser();

	LightmapDenoiserOIDN();
	~LightmapDenoiserOIDN();
};

#endif // LIGHTMAP_DENOISER_H
