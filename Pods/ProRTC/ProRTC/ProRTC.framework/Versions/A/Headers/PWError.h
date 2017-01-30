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
  PWErrorRoomFull = -3,
  
  /** Client attempted to send a signal with an invalid type. */
  PWErrorInvalidSignalType = -4,
  
  /** Client attempted to send a signal with a data that is greater than
   the maximum length (8KB). */
  PWErrorSignalDataTooLong = -5
};

#endif /* PWError_h */
