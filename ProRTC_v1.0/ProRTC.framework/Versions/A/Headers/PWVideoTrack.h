//
//  PWVideoTrack.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

// webrtc
@class RTCVideoTrack;

// prortc
@class PWEAGLVideoView;

/**
 *  `PWVideoTrack` is an Objective-C wrapper for webrtc video track interface.
 */
@interface PWVideoTrack : NSObject

/** @name Initializing */

/**
 *  Initialize video track wrapper.
 *
 *  @param track An object of `RTCVideoTrack`.
 *
 *  @return Instance of `PWVideoTrack`.
 */
- (instancetype)initWithTrack:(RTCVideoTrack *)track;


/** @name Video rendering */

/**
 * Start video rendering.
 * @param rendererView `PWEAGLVideoView` object on which this track will be rendered.
 */
- (void)bindRendererView:(PWEAGLVideoView *)rendererView;

/**
 * Stop video rendering.
 * @param rendererView `PWEAGLVideoView` object on which this track is currently displaying.
 */
- (void)unBindRendererView:(PWEAGLVideoView *)rendererView;

@end
