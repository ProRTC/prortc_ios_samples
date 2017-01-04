//
//  PWEAGLVideoView.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PWVideoTrack;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWEAGLVideoView` class renders video frames from track in its bounds using
 *  OpenGLES 2.0.
 */
@interface PWEAGLVideoView : UIView

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
