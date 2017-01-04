//
//  PWMediaStream.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWMediaStream` is a collection of audio and video tracks.
 */
@interface PWMediaStream : NSObject

/**
 *  Attrubute determines that audio of media stream is enabled or disabled.
 */
@property (nonatomic, assign, getter = isAudioEnabled) BOOL audioEnabled;

/**
 *  Attrubute determines that video of media stream is enabled or disabled.
 */
@property (nonatomic, assign, getter = isVideoEnabled) BOOL videoEnabled;

/**
 *  Attrubute determines that audio track is available.
 */
@property (nonatomic, assign, getter = isAudioTrackAvailable) BOOL audioTrackAvailable;

/**
 *  Attrubute determines that video track is available.
 */
@property (nonatomic, assign, getter = isVideoTrackAvailable) BOOL videoTrackAvailable;

/**
 *  Collection of video tracks in media stream.
 */
@property (nonatomic, strong, readonly, nullable) NSArray *videoTracks;

/**
 *  Collection of audio tracks in media stream.
 */
@property (nonatomic, strong, readonly, nullable) NSArray *audioTracks;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWMediaStream cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END

