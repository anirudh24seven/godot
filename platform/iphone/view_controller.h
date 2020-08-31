
/*  view_controller.h                                                    */



#import <GameKit/GameKit.h>
#import <UIKit/UIKit.h>

@class GodotView;

@interface ViewController : UIViewController <GKGameCenterControllerDelegate>

- (GodotView *)godotView;

// MARK: Native Video Player

- (BOOL)playVideoAtPath:(NSString *)filePath volume:(float)videoVolume audio:(NSString *)audioTrack subtitle:(NSString *)subtitleTrack;
- (BOOL)isVideoPlaying;
- (void)pauseVideo;
- (void)unpauseVideo;
- (void)stopVideo;

@end
