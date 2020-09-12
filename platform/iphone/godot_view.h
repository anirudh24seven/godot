
/*  godot_view.h                                                         */

#import <UIKit/UIKit.h>

class String;

@protocol DisplayLayer;
@protocol GodotViewRendererProtocol;

@interface GodotView : UIView <UIKeyInput>

@property(assign, nonatomic) id<GodotViewRendererProtocol> renderer;

@property(assign, readonly, nonatomic) BOOL isActive;

@property(assign, nonatomic) BOOL useCADisplayLink;
@property(strong, readonly, nonatomic) CALayer<DisplayLayer> *renderingLayer;
@property(assign, readonly, nonatomic) BOOL canRender;

@property(assign, nonatomic) NSTimeInterval renderingInterval;

- (CALayer<DisplayLayer> *)initializeRenderingForDriver:(NSString *)driverName;
- (void)stopRendering;
- (void)startRendering;

- (BOOL)becomeFirstResponderWithString:(String)p_existing;

@end
