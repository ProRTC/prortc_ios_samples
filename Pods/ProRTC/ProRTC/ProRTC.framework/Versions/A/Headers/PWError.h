//
//  PWError.h
//  ProRTC
//
//  Copyright (c) 2017 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef PWError_h
#define PWError_h

extern NSString *const kPWErrorDomain;

/**
 *  An enum indicates the errors that can be raised by the ProRTC SDK.
 */
typedef NS_ENUM(NSInteger, PWError) {
    
    /** Server is disconnected or not responding */
    PWErrorClosedAbnormally = -1,
    
    /** Client attempted to join room which is locked by room owner */
    PWErrorRoomLocked = -2,
    
    /** Client attempted to join room which is full */
    PWErrorRoomFull = -3
};

#endif /* PWError_h */
