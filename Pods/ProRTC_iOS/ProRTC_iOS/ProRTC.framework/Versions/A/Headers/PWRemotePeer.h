//
//  PWRemotePeer.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWRemotePeer` represents remote participant in a room.
 */
@interface PWRemotePeer : NSObject

/**
 *  An unique id of participant.
 */
@property (nonatomic, copy, readonly) NSString *peerId;

/**
 *  Name of participant, If given.
 */
@property (nonatomic, copy, readonly) NSString *displayName;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWRemotePeer cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END

