
/*  vulkan_context_x11.cpp                                               */



#include "vulkan_context_x11.h"
#include <vulkan/vulkan_xlib.h>

const char *VulkanContextX11::_get_platform_surface_extension() const {
	return VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
}

Error VulkanContextX11::window_create(DisplayServer::WindowID p_window_id, ::Window p_window, Display *p_display, int p_width, int p_height) {
	VkXlibSurfaceCreateInfoKHR createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.dpy = p_display;
	createInfo.window = p_window;

	VkSurfaceKHR surface;
	VkResult err = vkCreateXlibSurfaceKHR(_get_instance(), &createInfo, nullptr, &surface);
	ERR_FAIL_COND_V(err, ERR_CANT_CREATE);
	return _window_create(p_window_id, surface, p_width, p_height);
}

VulkanContextX11::VulkanContextX11() {
}

VulkanContextX11::~VulkanContextX11() {
}
