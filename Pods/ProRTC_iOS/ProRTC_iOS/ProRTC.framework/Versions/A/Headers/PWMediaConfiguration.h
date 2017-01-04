//
//  PWMediaConfiguration.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>

/**
 *  Maximum audio bitrate. (bps)
 */
extern int64_t const PWMediaSessionMaximumAudioRate;

/**
 *  Maximum video bitrate. (bps)
 */
extern int64_t const PWMediaSessionMaximumVideoRate;

/**
 *  Preferred video dimensions.
 */
typedef NS_ENUM(NSUInteger, PWVideoCapturePreset) {
    
    /** Produces a medium quality 4:3 output (640x480) suitable for modern devices. */
    PWVideoCapturePreset640x480,
    /** Produces a high quality 16:9 540p output (960x540). */
    PWVideoCapturePreset960x540,
    /** Produces a high quality 16:9 720p output (1280x720). */
    PWVideoCapturePreset1280x720
};

/**
 *  Video capture source.
 */
typedef NS_ENUM(NSUInteger, PWCameraPosition) {
    
    /** Back facing device camera. */
    PWCameraPositionBack = 0,
    /** Front facing device camera. */
    PWCameraPositionFront
};

/**
 *  Audio coding/decoding program.
 */
typedef NS_ENUM(NSUInteger, PWAudioCodec)
{
    /** Opus audio codec is wideband, and higher quality. */
    PWAudioCodecOpus = 0,
    /** ISAC is lower quality, but more compatible. */
    PWAudioCodecISAC
};

/**
 *  Video coding/decoding program.
 */
typedef NS_ENUM(NSUInteger, PWVideoCodec)
{
    /** VP8 is stable and widely used - code & decode via libvpx */
    PWVideoCodecVP8 = 0,
    /** 
     *  H.264 is hardware acceleration code/decode.
     *  Saves battery life & CPU - improves user experience.
     */
    PWVideoCodecH264
};


NS_ASSUME_NONNULL_BEGIN

/** 
 *  @brief The `PWMediaConfiguration` class manages Media configurations.
 *
 *  @discussion Rendering, Audio/Video codecs, Audio/Video bandwidth control, Video dimensions
 */
@interface PWMediaConfiguration : NSObject

/**
 *  The `PWAudioCodec`. Preferred audio codec.
 */
@property (nonatomic, assign) PWAudioCodec preferredAudioCodec;

/**
 *  The `PWVideoCodec`. Preferred video codec.
 */
@property (nonatomic, assign) PWVideoCodec preferredVideoCodec;

/**
 *  @brief Maximum bandwidth for audio (bps).
 *
 *  @discussion Default is 120 kbps.
 */
@property (nonatomic, assign) int64_t maxAudioBitrate;

/**
 *  @brief Maximum bandwidth for video (bps).
 *
 *  @discussion Default is 1.5 mbps.
 */
@property (nonatomic, assign) int64_t maxVideoBitrate;

/**
 *  @brief The `PWVideoCapturePreset`. Preferred video dimensions.
 * 
 *  @discussion Default is 640x480.
 */
@property (nonatomic, assign) PWVideoCapturePreset preferredVideoCapturePreset;

/**
 *  The `PWCameraPosition`. Camera device position.
 */
@property (nonatomic, assign) PWCameraPosition cameraPosition;

/**
 *  @brief Get default configuration of media.
 *
 *  @return A `PWMediaConfiguration` object.
 */
+ (instancetype)defaultConfiguration;

/**
 *  @brief Get dimensions for video preset.
 *
 *  @param preset The `PWVideoCapturePreset`.
 *
 *  @return The video dimensions for the given preset.
 */
+ (CMVideoDimensions)dimensionsForPreset:(PWVideoCapturePreset)preset;

@end

NS_ASSUME_NONNULL_END

