//
//  PWVideoTrack.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWVideoTrack` represents video and provides an interface to render video frames from the track.
 */
@interface PWVideoTrack : NSObject

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWVideoTrack cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END

