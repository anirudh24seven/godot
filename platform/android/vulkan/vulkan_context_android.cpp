
/*  vulkan_context_android.cpp                                           */

#include "vulkan_context_android.h"
#include <vulkan/vulkan_android.h>

const char *VulkanContextAndroid::_get_platform_surface_extension() const {
	return VK_KHR_ANDROID_SURFACE_EXTENSION_NAME;
}

int VulkanContextAndroid::window_create(ANativeWindow *p_window, int p_width, int p_height) {
	VkAndroidSurfaceCreateInfoKHR createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.window = p_window;

	VkSurfaceKHR surface;
	VkResult err = vkCreateAndroidSurfaceKHR(_get_instance(), &createInfo, nullptr, &surface);
	if (err != VK_SUCCESS) {
		ERR_FAIL_V_MSG(-1, "vkCreateAndroidSurfaceKHR failed with error " + itos(err));
	}

	return _window_create(DisplayServer::MAIN_WINDOW_ID, surface, p_width, p_height);
}

VulkanContextAndroid::VulkanContextAndroid() {
	// TODO: fix validation layers
	use_validation_layers = false;
}

VulkanContextAndroid::~VulkanContextAndroid() {
}
