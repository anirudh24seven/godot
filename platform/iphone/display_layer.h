
/*  display_layer.h                                                      */



#import <OpenGLES/EAGLDrawable.h>
#import <QuartzCore/QuartzCore.h>

@protocol DisplayLayer <NSObject>

- (void)renderDisplayLayer;
- (void)initializeDisplayLayer;
- (void)layoutDisplayLayer;

@end

// An ugly workaround for iOS simulator
#if defined(TARGET_OS_SIMULATOR) && TARGET_OS_SIMULATOR
#if defined(__IPHONE_13_0)
API_AVAILABLE(ios(13.0))
@interface GodotMetalLayer : CAMetalLayer <DisplayLayer>
#else
@interface GodotMetalLayer : CALayer <DisplayLayer>
#endif
#else
@interface GodotMetalLayer : CAMetalLayer <DisplayLayer>
#endif
@end

API_DEPRECATED("OpenGLES is deprecated", ios(2.0, 12.0))
@interface GodotOpenGLLayer : CAEAGLLayer <DisplayLayer>

@end
