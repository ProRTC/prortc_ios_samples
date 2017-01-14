//
//  PWLocalParticipant.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PWLocalMedia;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWLocalParticipant` represents local client in a room.
 */
@interface PWLocalParticipant : NSObject

/**
 *  @brief The Local participant's server identifier.
 */
@property (nonatomic, copy, readonly) NSString *sid;

/**
 *  @brief Determines the Local participant is an initiator/owner of the room.
 */
@property (assign, nonatomic, readonly, getter=isInitiator) BOOL initiator;

/**
 *  @brief The Local participant's name. If given.
 */
@property (nonatomic, copy, readonly, nullable) NSString *name;

/**
 *  @brief The Local participant's media which is shared with other participants in a room.
 */
@property (nonatomic, strong, readonly, nullable) PWLocalMedia *media;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWLocalParticipant cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END
