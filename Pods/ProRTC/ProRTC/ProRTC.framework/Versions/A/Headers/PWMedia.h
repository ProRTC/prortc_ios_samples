//
//  PWMedia.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PWAudioTrack;
@class PWVideoTrack;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWMedia` is a collection of audio and video tracks shared by a remote participant.
 */
@interface PWMedia : NSObject

/**
 *  @brief A collection of audio tracks.
 */
@property (nonatomic, copy, readonly) NSArray<PWAudioTrack *> *audioTracks;

/**
 *  @brief A collection of video tracks.
 */
@property (nonatomic, copy, readonly) NSArray<PWVideoTrack *> *videoTracks;

/**
 *  @brief Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWMedia cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END
