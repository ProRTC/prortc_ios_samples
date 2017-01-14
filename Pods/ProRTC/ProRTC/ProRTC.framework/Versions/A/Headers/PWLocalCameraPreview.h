//
//  PWLocalCameraPreview.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PWVideoTrack;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWLocalCameraPreview` class renders local video from an
 *  AVCaptureSession.
 */
@interface PWLocalCameraPreview : UIView

/**
 *  @brief Starts rendering local video from local video track.
 * 
 *  @param videoTrack The track of local video.
 */
- (void)bindWithLocalVideoTrack:(PWVideoTrack *)videoTrack;

@end

NS_ASSUME_NONNULL_END
