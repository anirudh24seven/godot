
/*  vulkan_context_x11.h                                                 */



#ifndef VULKAN_DEVICE_X11_H
#define VULKAN_DEVICE_X11_H

#include "drivers/vulkan/vulkan_context.h"
#include <X11/Xlib.h>

class VulkanContextX11 : public VulkanContext {
	virtual const char *_get_platform_surface_extension() const;

public:
	Error window_create(DisplayServer::WindowID p_window_id, ::Window p_window, Display *p_display, int p_width, int p_height);

	VulkanContextX11();
	~VulkanContextX11();
};

#endif // VULKAN_DEVICE_X11_H
