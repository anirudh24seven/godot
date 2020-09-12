
/*  vulkan_context_win.cpp                                               */

#include "vulkan_context_win.h"
#include <vulkan/vulkan_win32.h>

const char *VulkanContextWindows::_get_platform_surface_extension() const {
	return VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
}

int VulkanContextWindows::window_create(DisplayServer::WindowID p_window_id, HWND p_window, HINSTANCE p_instance, int p_width, int p_height) {
	VkWin32SurfaceCreateInfoKHR createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.hinstance = p_instance;
	createInfo.hwnd = p_window;

	VkSurfaceKHR surface;
	VkResult err = vkCreateWin32SurfaceKHR(_get_instance(), &createInfo, nullptr, &surface);
	ERR_FAIL_COND_V(err, -1);
	return _window_create(p_window_id, surface, p_width, p_height);
}

VulkanContextWindows::VulkanContextWindows() {
}

VulkanContextWindows::~VulkanContextWindows() {
}
