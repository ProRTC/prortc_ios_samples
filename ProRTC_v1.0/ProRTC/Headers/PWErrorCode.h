//
//  PWErrorCode.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#ifndef PWErrorCode_h
#define PWErrorCode_h

/**
 * `kWebSocketErrorCode` indicates the connection error code values.
 */
typedef NS_ENUM(NSInteger, kWebSocketErrorCode) {
    
    /** Server is disconnected or not responding */
    kWebSocketErrorCode_ClosedAbnormally,
    
    /** Client attempted to join room which is locked by room owner */
    kWebSocketErrorCode_RoomLocked,
    
    /** Client attempted to join room which is full */
    kWebSocketErrorCode_RoomFull
};

#endif /* PWErrorCode_h */
