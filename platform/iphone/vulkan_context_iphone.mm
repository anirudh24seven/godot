
/*  vulkan_context_iphone.mm                                             */



#include "vulkan_context_iphone.h"
#include <vulkan/vulkan_ios.h>

const char *VulkanContextIPhone::_get_platform_surface_extension() const {
	return VK_MVK_IOS_SURFACE_EXTENSION_NAME;
}

Error VulkanContextIPhone::window_create(DisplayServer::WindowID p_window_id,
		CALayer *p_metal_layer, int p_width,
		int p_height) {
	VkIOSSurfaceCreateInfoMVK createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
	createInfo.pNext = NULL;
	createInfo.flags = 0;
	createInfo.pView = p_metal_layer;

	VkSurfaceKHR surface;
	VkResult err =
			vkCreateIOSSurfaceMVK(_get_instance(), &createInfo, NULL, &surface);
	ERR_FAIL_COND_V(err, ERR_CANT_CREATE);

	return _window_create(p_window_id, surface, p_width, p_height);
}

VulkanContextIPhone::VulkanContextIPhone() {}

VulkanContextIPhone::~VulkanContextIPhone() {}
