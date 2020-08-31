
/*  app_delegate.h                                                       */



#import <UIKit/UIKit.h>

@class ViewController;

// FIXME: Add support for both GLES2 and Vulkan when GLES2 is implemented again,
// so it can't be done with compilation time branching.
//#if defined(OPENGL_ENABLED)
//@interface AppDelegate : NSObject <UIApplicationDelegate, GLViewDelegate> {
//#endif
//#if defined(VULKAN_ENABLED)
@interface AppDelegate : NSObject <UIApplicationDelegate>
//#endif

@property(strong, nonatomic) UIWindow *window;
@property(strong, class, readonly, nonatomic) ViewController *viewController;

@end
