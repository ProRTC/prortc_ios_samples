//
//  PWErrorCode.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#ifndef PWErrorCode_h
#define PWErrorCode_h

/**
 *  ProRTC framework error codes.
 */
typedef NS_ENUM(NSInteger, PWErrorCode) {
    
    /** Server is disconnected or not responding */
    PWErrorCodeClosedAbnormally,
    
    /** Client attempted to join room which is locked by room owner */
    PWErrorCodeRoomLocked,
    
    /** Client attempted to join room which is full */
    PWErrorCodeRoomFull
};

#endif /* PWErrorCode_h */
