//
//  PWMediaConfiguration.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@import CoreMedia;

UIKIT_EXTERN double PWMediaSessionFrameWeightExponentDenominator;

/**
 * `PWRendererType` defines rendering type values.
 */
typedef NS_OPTIONS(NSUInteger, PWRendererType)
{
    /** Rendering type AVSampleBuffer */
    PWRendererTypeSampleBuffer,
    /** Rendering type OpenGLES */
    PWRendererTypeOpenGLES,
    /** Rendering type Quartz */
    PWRendererTypeQuartz
};

/**
 * `PWCameraPosition` defines camera device (Front/Back) values.
 */
typedef NS_ENUM(NSUInteger, PWCameraPosition) {
    
    /** Camera position back. */
    PWCameraPositionBack = 1,
    
    /** Camera position front. */
    PWCameraPositionFront = 2
};

/**
 * `PWAudioCodec` defines audio codecs.
 */
typedef NS_ENUM(NSUInteger, PWAudioCodec)
{
    /** The Opus audio codec is wideband, and higher quality. */
    PWAudioCodecOpus = 0,
    /** ISAC is lower quality, but more compatible. */
    PWAudioCodecISAC = 1
};

/**
 * `PWVideoCodec` defines video codecs.
 */
typedef NS_ENUM(NSUInteger, PWVideoCodec)
{
    /** Stable, software VP8 encode & decode via libvpx */
    PWVideoCodecVP8 = 0,
    /** Experimental, hardware H.264 encode & decode via VideoToolbox. */
    PWVideoCodecH264 = 1
};

/**
 * `PWPixelFormat` defines pixel formating values.
 */
typedef NS_ENUM(OSType, PWPixelFormat)
{
    /** 32 bit BGRA */
    PWPixelFormat32BGRA = kCVPixelFormatType_32BGRA,
    /** Bi-Planar Component Y'CbCr 8-bit 4:2:0, video-range (luma=[16,235] chroma=[16,240]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
    PWPixelFormatYUV420BiPlanarVideoRange = kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,
    /** Bi-Planar Component Y'CbCr 8-bit 4:2:0, full-range (luma=[0,255] chroma=[1,255]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
    PWPixelFormatYUV420BiPlanarFullRange = kCVPixelFormatType_420YpCbCr8BiPlanarFullRange,
};


typedef struct PWVideoFormat {
    CMVideoDimensions dimensions;
    PWPixelFormat pixelFormat;
    double frameRate;
} PWVideoFormat;


UIKIT_EXTERN NSUInteger PWMediaSessionMaximumAudioRate;
UIKIT_EXTERN NSUInteger PWMediaSessionMaximumVideoRate;

UIKIT_EXTERN NSUInteger PWMediaSessionMaximumAudioRateMultiparty;
UIKIT_EXTERN NSUInteger PWMediaSessionMaximumVideoRateMultiparty;

UIKIT_EXTERN double PWMediaSessionTargetBpp;


static inline NSUInteger WRTCVideoFormatComputePeakRate(PWVideoFormat format, double targetBpp, NSUInteger maxRate)
{
    /*
     Perform a naive estimate of the maximum encoder rate suitable for the given video format.
     Apply an exponential frame rate weighting so that lower FPS is not data starved.
     Units are kbps.
     */
    
    double frameRate = format.frameRate;
    double frameRateWeight = exp((30.0 - frameRate) / (PWMediaSessionFrameWeightExponentDenominator * frameRate));
    double pixelRate = (double)format.dimensions.width * (double)format.dimensions.height * frameRate;
    double recommendedRate = pixelRate * targetBpp * frameRateWeight;
    recommendedRate = MIN(recommendedRate, maxRate);
    
    return round(recommendedRate);
}

/** The `PWMediaConfiguration` class manages Media properties.
 *
 * `PWMediaConfiguration` provides support for the following features:
 *
 *  - Rendering.
 *  - Audio/Video codecs.
 *  - Audio/Video bandwidth control.
 *  - Frame rate & pixel formats.
 *  - Computes prefered receiving video format on the basis of device capabilities and performance.
 */
@interface PWMediaConfiguration : NSObject


/** @name Media properties */

/**
 * Determines video rendering type <PWRendererType>.
 */
@property (nonatomic, assign) PWRendererType rendererType;

/**
 * Preferred audio codec <PWAudioCodec>.
 */
@property (nonatomic, assign) PWAudioCodec preferredAudioCodec;

/**
 * Preferred video codec <PWVideoCodec>.
 */
@property (nonatomic, assign) PWVideoCodec preferredVideoCodec;

/**
 * Maximum bandwidth for audio.
 */
@property (nonatomic, assign) NSUInteger maxAudioBitrate;

/**
 * Maximum bandwidth for video.
 */
@property (nonatomic, assign) NSUInteger maxVideoBitrate;

/**
 * Preferred video receiving format for the device.
 */
@property (nonatomic, assign) PWVideoFormat preferredReceiverFormat;

/**
 * Camera device position <PWCameraPosition>.
 */
@property (nonatomic, assign) PWCameraPosition cameraPosition;


/** @name Default media configuration */

/**
 * Get default configuration of media.
 * @return `PWMediaConfiguration` object.
 */
+ (instancetype)defaultConfiguration;


/** @name Video capturing */

/**
 * Get Preferred video receiving format for the device.
 * @return Video format.
 */
+ (PWVideoFormat)videoCaptureFormat;

@end
