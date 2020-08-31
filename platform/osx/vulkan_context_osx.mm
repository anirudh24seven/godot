
/*  vulkan_context_osx.mm                                                */



#include "vulkan_context_osx.h"
#include <vulkan/vulkan_macos.h>

const char *VulkanContextOSX::_get_platform_surface_extension() const {
	return VK_MVK_MACOS_SURFACE_EXTENSION_NAME;
}

Error VulkanContextOSX::window_create(DisplayServer::WindowID p_window_id, id p_window, int p_width, int p_height) {
	VkMacOSSurfaceCreateInfoMVK createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
	createInfo.pNext = NULL;
	createInfo.flags = 0;
	createInfo.pView = p_window;

	VkSurfaceKHR surface;
	VkResult err = vkCreateMacOSSurfaceMVK(_get_instance(), &createInfo, NULL, &surface);
	ERR_FAIL_COND_V(err, ERR_CANT_CREATE);
	return _window_create(p_window_id, surface, p_width, p_height);
}

VulkanContextOSX::VulkanContextOSX() {
}

VulkanContextOSX::~VulkanContextOSX() {
}
