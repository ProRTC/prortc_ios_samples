//
//  RTCMediaStream+Configuration.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import "RTCMediaStream.h"

/**
 * The `RTCMediaStream+Configuration` category provides audio/video availability.
 */
@interface RTCMediaStream (Configuration)

/** @name Properties */

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

@end
