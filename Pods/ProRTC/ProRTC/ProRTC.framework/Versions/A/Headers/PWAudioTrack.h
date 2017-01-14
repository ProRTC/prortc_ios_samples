//
//  PWAudioTrack.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "PWTrack.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWAudioTrack` represents a local or remote audio track.
 */
@interface PWAudioTrack : PWTrack

/**
 *  @brief Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWAudioTrack cannot be created explicitly.")));

@end

@class PWAudioConstraints;

/**
 *  `PWLocalAudioTrack` represents an audio track of your device.
 */
@interface PWLocalAudioTrack : PWAudioTrack

/**
 *  @brief The constraints of this audio track.
 */
@property (nonatomic, strong, readonly, nonnull) PWAudioConstraints *constraints;

/**
 *  @brief Indicates if the track is enabled.
 *
 *  @discussion Use this to enable or disbale audio for other participants in the room.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

@end


NS_ASSUME_NONNULL_END
