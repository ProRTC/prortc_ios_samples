//
//  PWTrack.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  `PWTrackState` represents the state of track.
 */
typedef NS_ENUM(NSInteger, PWTrackState) {
    /**
     *  Track live.
     */
    PWTrackStateLive,
    /**
     *  Track ended.
     */
    PWTrackStateEnded
};

NS_ASSUME_NONNULL_BEGIN

extern NSString * const PWTrackKindAudio;
extern NSString * const PWTrackKindVideo;

/**
 *  @brief `PWTrack` is the base class of Audio/Video tracks.
 */
@interface PWTrack : NSObject

/**
 *  @brief The kind of track.
 *
 *  @discussion 'audio' If this track represents an audio track,
 *  'video' If this track represents a video track.
 */
@property (nonatomic, copy, readonly) NSString *kind;

/**
 *  @brief An identifier for the track.
 */
@property (nonatomic, copy, readonly) NSString *trackId;

/**
 *  @brief The state represents, If the track is enabled or not.
 */
@property (nonatomic, assign, readonly, getter=isEnabled) BOOL enabled;

/**
 *  @brief The current state of the track.
 */
@property (nonatomic, assign, readonly) PWTrackState state;

/**
 *  @brief Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWTrack cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END
