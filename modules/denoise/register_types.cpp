
/*  register_types.cpp                                                   */



#include "register_types.h"
#include "core/engine.h"
#include "lightmap_denoiser.h"

void register_denoise_types() {
	LightmapDenoiserOIDN::make_default_denoiser();
}

void unregister_denoise_types() {
}
