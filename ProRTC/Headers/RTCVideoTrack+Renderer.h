//
//  RTCVideoTrack+Renderer.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import "RTCVideoTrack.h"

@class RTCEAGLVideoView;

/**
 * The `RTCVideoTrack+Renderer` category manages rendering of video tracks.
 */
@interface RTCVideoTrack (Renderer)

/** @name Video rendering */

/**
 * Start video rendering.
 * @param rendererView A view object on which video will display.
 */
- (void)bindRendererView:(RTCEAGLVideoView *)rendererView;

/**
 * Stop video rendering.
 * @param rendererView A view object on which video is displaying.
 */
- (void)unBindRendererView:(RTCEAGLVideoView *)rendererView;

@end
