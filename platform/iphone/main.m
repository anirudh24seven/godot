
/*  main.m                                                               */



#import "app_delegate.h"

#import <UIKit/UIKit.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

int gargc;
char **gargv;

int main(int argc, char *argv[]) {
#if defined(VULKAN_ENABLED)
	//MoltenVK - enable full component swizzling support
	setenv("MVK_CONFIG_FULL_IMAGE_VIEW_SWIZZLE", "1", 1);
#endif

	printf("*********** main.m\n");
	gargc = argc;
	gargv = argv;

	printf("running app main\n");
	@autoreleasepool {
		UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
	}
	printf("main done\n");
	return 0;
}
