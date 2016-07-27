//
//  PWEAGLVideoView.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

// webrtc
@class RTCEAGLVideoView;
@class RTCI420Frame;

/**
 * `PWEAGLVideoView` class is an Objective-C wrapper for webrtc video renderer which renders i420 frames in its bounds using
 * OpenGLES 2.0.
 */
@interface PWEAGLVideoView : UIView

/** @name Properties */

/**
 *  Webrtc default renderer view.
 */
@property (strong, nonatomic, readonly) RTCEAGLVideoView *videoView;


/** @name Rendering */

/**
 *  Render frame.
 *
 *  @param frame The frame to be displayed.
 */
- (void)renderFrame:(RTCI420Frame *)frame;

@end
