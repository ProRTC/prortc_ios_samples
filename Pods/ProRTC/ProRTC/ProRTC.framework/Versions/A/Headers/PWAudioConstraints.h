//
//  PWAudioConstraints.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWAudioConstraintsOptions` constructs `PWAudioConstraints`.
 */
@interface PWAudioConstraintsOptions : NSObject

/**
 *  @brief Automatically applies gain so that voices are easier to understand. Defaults to `NO`.
 */
@property (nonatomic, assign) BOOL autoGainControl;

/**
 *  @brief Reduces background noise levels. Defaults to `NO`.
 */
@property (nonatomic, assign) BOOL noiseReduction;

/**
 *  @brief Maximum bandwidth for audio. By default No Limit.
 */
@property (nonatomic, strong) NSNumber *maxBitrateBps;

@end


/**
 *  `PWAudioConstraints` allows client to define audio constraints as per requirement.
 */
@interface PWAudioConstraints : NSObject

/**
 *  Automatically applies gain so that voices are easier to understand. Defaults to `NO`.
 */
@property (nonatomic, assign, readonly) BOOL autoGainControl;

/**
 *  Reduces background noise levels. Defaults to `NO`.
 */
@property (nonatomic, assign, readonly) BOOL noiseReduction;

/**
 *  @brief Maximum bandwidth for audio. By default No Limit.
 */
@property (nonatomic, strong, readonly) NSNumber *maxBitrateBps;

/**
 *  @brief Creates default constraints.
 *
 *  @return An instance of `PWAudioConstraints`.
 */
+ (instancetype)constraints;

/**
 *  @brief Constructs `PWAudioConstraints`.
 *
 *  @param options The audio constraints options.
 *
 *  @return An instance of `PWAudioConstraints`.
 */
+ (instancetype)constraintsWithOptions:(PWAudioConstraintsOptions *)options;

@end

NS_ASSUME_NONNULL_END
