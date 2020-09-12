
/*  vulkan_context_osx.h                                                 */

#ifndef VULKAN_DEVICE_OSX_H
#define VULKAN_DEVICE_OSX_H

#include "drivers/vulkan/vulkan_context.h"
#include <AppKit/AppKit.h>

class VulkanContextOSX : public VulkanContext {
	virtual const char *_get_platform_surface_extension() const;

public:
	Error window_create(DisplayServer::WindowID p_window_id, id p_window, int p_width, int p_height);

	VulkanContextOSX();
	~VulkanContextOSX();
};

#endif // VULKAN_DEVICE_OSX_H
