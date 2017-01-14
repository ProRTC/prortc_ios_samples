//
//  PWLocalMedia.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PWAudioTrack;
@class PWVideoTrack;
@class PWLocalAudioTrack;
@class PWLocalVideoTrack;
@class PWAudioConstraints;
@class PWVideoConstraints;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWLocalMedia` is a collection of local audio and video tracks of client and shared with other,
 *  participants in the room.
 */
@interface PWLocalMedia : NSObject

/**
 *  @brief A collection of audio tracks.
 */
@property (nonatomic, strong, readonly) NSArray<PWLocalAudioTrack *> *audioTracks;

/**
 *  @brief A collection of video tracks.
 */
@property (nonatomic, strong, readonly) NSArray<PWLocalVideoTrack *> *videoTracks;

/** 
 *  @brief Returns whether rear-facing camera is available for use.
 */
@property(nonatomic, readonly) BOOL canUseBackCamera;

/** 
 *  @brief Switches the camera (either front or back).
 */
@property(nonatomic, assign) BOOL useBackCamera;

/**
 *  @brief Adds a local audio track to `PWLocalMedia`.
 *
 *  @param enabled Specifies if `PWLocalAudioTrack` should be enabled or disabled initially.
 *
 *  @return An instance of `PWLocalAudioTrack` if successful, or `nil` if not.
 */
- (nullable PWLocalAudioTrack *)addAudioTrack:(BOOL)enabled;

/**
 *  @brief Adds a local audio track to `PWLocalMedia`.
 *
 *  @param enabled Specifies if `PWLocalAudioTrack` should be enabled or disabled initially.
 *  @param constraints The audio constraints.
 *
 *  @return An instance of PWLocalAudioTrack if successful, or `nil` if not.
 */
- (nullable PWLocalAudioTrack *)addAudioTrack:(BOOL)enabled
                                  constraints:(nullable PWAudioConstraints *)constraints;

/**
 *  @brief Adds a local video track to `PWLocalMedia`.
 *
 *  @param enabled Specifies if `PWLocalVideoTrack` should be enabled or disabled initially.
 *
 *  @return An instance of `PWLocalVideoTrack` if successful, or `nil` if not.
 */
- (nullable PWLocalVideoTrack *)addVideoTrack:(BOOL)enabled;

/**
 *  @brief Adds a local video track to `PWLocalMedia`.
 *
 *  @param enabled Specifies if `PWLocalVideoTrack` should be enabled or disabled initially.
 *  @param constraints The video constraints.
 *
 *  @return An instance of `PWLocalVideoTrack` if successful, or `nil` if not.
 */
- (nullable PWLocalVideoTrack *)addVideoTrack:(BOOL)enabled
                                  constraints:(PWVideoConstraints *)constraints;

@end

NS_ASSUME_NONNULL_END
