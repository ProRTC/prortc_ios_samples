//
//  PWVideoConstraints.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

/**
 *  Produces smallest possible size, useful for multi-party.
 */
extern CMVideoDimensions const PWVideoConstraintsSize352x288;

/**
 *  Produces high quality, 4:3 output (640x480).
 */
extern CMVideoDimensions const PWVideoConstraintsSize640x480;

/**
 *  Produces quarter HD quality, 16:9 540p output (960x540).
 */
extern CMVideoDimensions const PWVideoConstraintsSize960x540;

/**
 *  Produces HD quality, 16:9 720p output (1280x720).
 */
extern CMVideoDimensions const PWVideoConstraintsSize1280x720;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWVideoConstraintsOptions` constructs `PWVideoConstraints`.
 */
@interface PWVideoConstraintsOptions : NSObject

/**
 *  @brief The dimensions of the camera feed. Default 640x480.
 */
@property (nonatomic, assign) CMVideoDimensions previewDimensions;

/**
 *  @brief Maximum bandwidth for video. By default No Limit.
 */
@property (nonatomic, strong) NSNumber *maxBitrateBps;

@end

/**
 *  `PWVideoConstraints` allows client to define video constraints as per requirement.
 */
@interface PWVideoConstraints : NSObject

/**
 *  @brief The dimensions of the camera feed. Default 640x480.
 */
@property (nonatomic, assign, readonly) CMVideoDimensions previewDimensions;

/**
 *  @brief Maximum bandwidth for video. By default No Limit.
 */
@property (nonatomic, strong, readonly) NSNumber *maxBitrateBps;

/**
 *  @brief Creates default constraints.
 *
 *  @return An instance of `PWVideoConstraints`.
 */
+ (instancetype)constraints;

/**
 *  @brief Constructs `PWVideoConstraints`.
 *
 *  @param options The video constraints options.
 *
 *  @return An instance of `PWVideoConstraints`.
 */
+ (instancetype)constraintsWithOptions:(PWVideoConstraintsOptions *)options;

@end

NS_ASSUME_NONNULL_END
