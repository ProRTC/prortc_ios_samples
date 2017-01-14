//
//  PWEAGLVideoView.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PWVideoTrack;
@class PWEAGLVideoView;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWEAGLVideoViewDelegate` responds on change in video size.
 */
@protocol PWEAGLVideoViewDelegate <NSObject>

/**
 *  @brief Invoked every time when the video size changes.
 *
 *  @discussion You can use this method to resize your view according to the new video size.
 *
 *  @param videoView The view whose video size is changed.
 *  @param size The new size of the video.
 */
- (void)videoView:(PWEAGLVideoView *)videoView didChangeVideoSize:(CGSize)size;

@end

/**
 *  `PWEAGLVideoView` class renders video frames from track in its bounds using
 *  OpenGLES 2.0.
 */
@interface PWEAGLVideoView : UIView

/**
 *  @brief The video view's delegate. Use this delegate to receive changes in video view's size.
 */
@property (nonatomic, weak, nullable) id<PWEAGLVideoViewDelegate> delegate;

/**
 *  @brief Start video rendering from track.
 *
 *  @param videoTrack The track to be rendered.
 */
- (void)bindTrack:(PWVideoTrack *)videoTrack;

/**
 *  @brief Stop video rendering.
 *
 *  @param videoTrack The track to be removed.
 */
- (void)unBindTrack:(PWVideoTrack *)videoTrack;

@end

NS_ASSUME_NONNULL_END
