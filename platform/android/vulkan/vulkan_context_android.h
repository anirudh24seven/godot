
/*  vulkan_context_android.h                                             */

#ifndef VULKAN_CONTEXT_ANDROID_H
#define VULKAN_CONTEXT_ANDROID_H

#include "drivers/vulkan/vulkan_context.h"

struct ANativeWindow;

class VulkanContextAndroid : public VulkanContext {
	virtual const char *_get_platform_surface_extension() const;

public:
	int window_create(ANativeWindow *p_window, int p_width, int p_height);

	VulkanContextAndroid();
	~VulkanContextAndroid();
};

#endif // VULKAN_CONTEXT_ANDROID_H
