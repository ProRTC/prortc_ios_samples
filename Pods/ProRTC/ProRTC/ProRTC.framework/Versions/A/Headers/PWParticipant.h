//
//  PWParticipant.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PWMedia;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWParticipant` represents a remote participant in a room.
 */
@interface PWParticipant : NSObject

/**
 *  @brief The participant's server identifier.
 */
@property (nonatomic, copy, readonly) NSString *sid;

/**
 *  @brief The participant's name. If given.
 */
@property (nonatomic, copy, readonly, nullable) NSString *name;

/**
 *  @brief The participant's media.
 */
@property (nonatomic, strong, readonly, nullable) PWMedia *media;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWParticipant cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END
