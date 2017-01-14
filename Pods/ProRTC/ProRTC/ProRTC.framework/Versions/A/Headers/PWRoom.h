//
//  PWRoom.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWRoom` represents a room in which client's session is connected.
 */
@interface PWRoom : NSObject

/**
 *  @brief The name of the room.
 */
@property (nonatomic, copy, readonly) NSString *name;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWRoom cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END

