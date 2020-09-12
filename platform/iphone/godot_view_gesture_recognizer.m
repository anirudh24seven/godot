
/*  godot_view_gesture_recognizer.m                                      */

#import "godot_view_gesture_recognizer.h"

// Using same delay interval that is used for `UIScrollView`
const NSTimeInterval kGLGestureDelayInterval = 0.150;

// Minimum distance for touches to move to fire
// a delay timer before scheduled time.
// Should be the low enough to not cause issues with dragging
// but big enough to allow click to work.
const CGFloat kGLGestureMovementDistance = 0.5;

@interface GodotViewGestureRecognizer ()

// Timer used to delay begin touch message.
// Should work as simple emulation of UIDelayedAction
@property(strong, nonatomic) NSTimer *delayTimer;

// Delayed touch parameters
@property(strong, nonatomic) NSSet *delayedTouches;
@property(strong, nonatomic) UIEvent *delayedEvent;

@end

@implementation GodotViewGestureRecognizer

- (instancetype)init {
	self = [super init];

	self.cancelsTouchesInView = YES;
	self.delaysTouchesBegan = YES;
	self.delaysTouchesEnded = YES;

	return self;
}

- (void)dealloc {
	if (self.delayTimer) {
		[self.delayTimer invalidate];
		self.delayTimer = nil;
	}

	if (self.delayedTouches) {
		self.delayedTouches = nil;
	}

	if (self.delayedEvent) {
		self.delayedEvent = nil;
	}

	[super dealloc];
}

- (void)delayTouches:(NSSet *)touches andEvent:(UIEvent *)event {
	[self.delayTimer fire];

	self.delayedTouches = touches;
	self.delayedEvent = event;

	self.delayTimer = [NSTimer
			scheduledTimerWithTimeInterval:kGLGestureDelayInterval
									target:self
								  selector:@selector(fireDelayedTouches:)
								  userInfo:nil
								   repeats:NO];
}

- (void)fireDelayedTouches:(id)timer {
	[self.delayTimer invalidate];
	self.delayTimer = nil;

	if (self.delayedTouches) {
		[self.view touchesBegan:self.delayedTouches withEvent:self.delayedEvent];
	}

	self.delayedTouches = nil;
	self.delayedEvent = nil;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	NSSet *cleared = [self copyClearedTouches:touches phase:UITouchPhaseBegan];
	[self delayTouches:cleared andEvent:event];
	[cleared release];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	NSSet *cleared = [self copyClearedTouches:touches phase:UITouchPhaseMoved];

	if (self.delayTimer) {
		// We should check if movement was significant enough to fire an event
		// for dragging to work correctly.
		for (UITouch *touch in cleared) {
			CGPoint from = [touch locationInView:self.view];
			CGPoint to = [touch previousLocationInView:self.view];
			CGFloat xDistance = from.x - to.x;
			CGFloat yDistance = from.y - to.y;

			CGFloat distance = sqrt(xDistance * xDistance + yDistance * yDistance);

			// Early exit, since one of touches has moved enough to fire a drag event.
			if (distance > kGLGestureMovementDistance) {
				[self.delayTimer fire];
				[self.view touchesMoved:cleared withEvent:event];
				[cleared release];
				return;
			}
		}

		[cleared release];
		return;
	}

	[self.view touchesMoved:cleared withEvent:event];
	[cleared release];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	[self.delayTimer fire];

	NSSet *cleared = [self copyClearedTouches:touches phase:UITouchPhaseEnded];
	[self.view touchesEnded:cleared withEvent:event];
	[cleared release];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	[self.delayTimer fire];
	[self.view touchesCancelled:touches withEvent:event];
};

- (NSSet *)copyClearedTouches:(NSSet *)touches phase:(UITouchPhase)phaseToSave {
	NSMutableSet *cleared = [touches mutableCopy];

	for (UITouch *touch in touches) {
		if (touch.phase != phaseToSave) {
			[cleared removeObject:touch];
		}
	}

	return cleared;
}

@end
