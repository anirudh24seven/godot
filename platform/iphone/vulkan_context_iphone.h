
/*  vulkan_context_iphone.h                                              */



#ifndef VULKAN_CONTEXT_IPHONE_H
#define VULKAN_CONTEXT_IPHONE_H

#include "drivers/vulkan/vulkan_context.h"

#import <UIKit/UIKit.h>

class VulkanContextIPhone : public VulkanContext {
	virtual const char *_get_platform_surface_extension() const;

public:
	Error window_create(DisplayServer::WindowID p_window_id, CALayer *p_metal_layer, int p_width, int p_height);

	VulkanContextIPhone();
	~VulkanContextIPhone();
};

#endif // VULKAN_CONTEXT_IPHONE_H
