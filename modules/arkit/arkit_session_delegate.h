
/*  arkit_session_delegate.h                                             */

#ifndef ARKIT_SESSION_DELEGATE_H
#define ARKIT_SESSION_DELEGATE_H

#import <ARKit/ARKit.h>
#import <UIKit/UIKit.h>

class ARKitInterface;

@interface ARKitSessionDelegate : NSObject <ARSessionDelegate> {
	ARKitInterface *arkit_interface;
}

@property(nonatomic) ARKitInterface *arkit_interface;

- (void)session:(ARSession *)session didAddAnchors:(NSArray<ARAnchor *> *)anchors API_AVAILABLE(ios(11.0));
- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<ARAnchor *> *)anchors API_AVAILABLE(ios(11.0));
- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<ARAnchor *> *)anchors API_AVAILABLE(ios(11.0));
@end

#endif /* !ARKIT_SESSION_DELEGATE_H */
