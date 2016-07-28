//
//  PWMediaStream.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

// webrtc
@class RTCMediaStream;
@class RTCVideoTrack;

/**
 *  `PWMediaStream` is an Objective-C wrapper for webrtc media stream interface.
 */
@interface PWMediaStream : NSObject

/** @name Properties */

/**
 * An object of webrtc media stream.
 */
@property (strong, nonatomic, readonly) RTCMediaStream *defaultStream;

/**
 * Attrubute determines that audio of media stream is enabled or disabled.
 */
@property (nonatomic, assign, getter = isAudioEnabled) BOOL audioEnabled;

/**
 * Attrubute determines that video of media stream is enabled or disabled.
 */
@property (nonatomic, assign, getter = isVideoEnabled) BOOL videoEnabled;

/**
 * Attrubute determines that audio track is available or not.
 */
@property (nonatomic, assign, getter = isAudioTrackAvailable) BOOL audioTrackAvailable;

/**
 * Attrubute determines that video track is available or not.
 */
@property (nonatomic, assign, getter = isVideoTrackAvailable) BOOL videoTrackAvailable;

/**
 * Collection of video tracks in media stream.
 */
@property (nonatomic, strong, readonly) NSArray *videoTracks;

/**
 * Collection of audio tracks in media stream.
 */
@property (nonatomic, strong, readonly) NSArray *audioTracks;


/** @name Initializing */

/**
 *  Initialize media stream wrapper.
 *
 *  @param mediaStream An object of webrtc media stream.
 *
 *  @return Instance of `PWMediaStream`.
 */
- (instancetype)initWithMediaStream:(RTCMediaStream *)mediaStream;


/** @name A/V Tracks */

/**
 *  Add video track to media stream.
 *
 *  @param videoTrack An object of `RTCVideoTrack`.
 */
- (void)addVideoTrack:(RTCVideoTrack *)videoTrack;

/**
 *  Remove video track from media stream.
 *
 *  @param videoTrack An object of `RTCVideoTrack`.
 */
- (void)removeVideoTrack:(RTCVideoTrack *)videoTrack;

@end
