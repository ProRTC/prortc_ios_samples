//
//  PWVideoTrack.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "PWTrack.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWVideoTrack` represents a local or remote video track.
 */
@interface PWVideoTrack : PWTrack

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWVideoTrack cannot be created explicitly.")));

@end

@class PWVideoConstraints;

/**
 *  `PWLocalVideoTrack` represents a video track of your device.
 */
@interface PWLocalVideoTrack : PWVideoTrack

/**
 *  @brief The constraints of this video track.
 */
@property (nonatomic, strong, readonly, nonnull) PWVideoConstraints *constraints;

/**
 *  @brief Indicates if the track is enabled.
 *
 *  @discussion Use this to enable or disbale video for other participants in the room.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

@end

NS_ASSUME_NONNULL_END

