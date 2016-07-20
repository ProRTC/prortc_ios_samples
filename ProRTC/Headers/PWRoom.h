//
//  PWRoom.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>

/**
 * The `PWRoom` class represents a room.
 */

@interface PWRoom : NSObject

/** @name Properties */

/**
 * Unique identifier of room connection.
 */
@property (nonatomic, copy, readonly) NSString *connectionId;

/**
 * Room Id OR Name.
 */
@property (nonatomic, copy, readonly) NSString *meetingId;

/** @name Initializing */

/**
 * Initialize room object.
 * @param meetingId Room Id OR Name.
 * @param connectionId Unique identifier of room connection (runtime created connection identifier, UUID A sequence of 128 bits that can guarantee uniqueness across space and time, defined by RFC 4122).
 * @return Instance of `PWRoom`.
 */
- (instancetype)initWithMeetingId:(NSString *)meetingId connectionId:(NSString *)connectionId;

@end
