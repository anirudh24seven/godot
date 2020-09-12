
/*  godot_view_gesture_recognizer.h                                      */

// GLViewGestureRecognizer allows iOS gestures to work currectly by
// emulating UIScrollView's UIScrollViewDelayedTouchesBeganGestureRecognizer.
// It catches all gestures incoming to UIView and delays them for 150ms
// (the same value used by UIScrollViewDelayedTouchesBeganGestureRecognizer)
// If touch cancelation or end message is fired it fires delayed
// begin touch immediately as well as last touch signal

#import <UIKit/UIKit.h>

@interface GodotViewGestureRecognizer : UIGestureRecognizer

- (instancetype)init;

@end
