
/*  register_types.cpp                                                   */

#include "register_types.h"

#include "core/project_settings.h"
#include "lightmapper_rd.h"
#include "scene/3d/lightmapper.h"

#ifndef _3D_DISABLED
static Lightmapper *create_lightmapper_rd() {
	return memnew(LightmapperRD);
}
#endif

void register_lightmapper_rd_types() {
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/low_quality_ray_count", 16);
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/medium_quality_ray_count", 64);
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/high_quality_ray_count", 256);
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/ultra_quality_ray_count", 1024);
	GLOBAL_DEF("rendering/gpu_lightmapper/performance/max_rays_per_pass", 32);
	GLOBAL_DEF("rendering/gpu_lightmapper/performance/region_size", 512);

	GLOBAL_DEF("rendering/gpu_lightmapper/quality/low_quality_probe_ray_count", 64);
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/medium_quality_probe_ray_count", 256);
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/high_quality_probe_ray_count", 512);
	GLOBAL_DEF("rendering/gpu_lightmapper/quality/ultra_quality_probe_ray_count", 2048);
	GLOBAL_DEF("rendering/gpu_lightmapper/performance/max_rays_per_probe_pass", 64);
#ifndef _3D_DISABLED
	ClassDB::register_class<LightmapperRD>();
	Lightmapper::create_gpu = create_lightmapper_rd;
#endif
}

void unregister_lightmapper_rd_types() {
}
