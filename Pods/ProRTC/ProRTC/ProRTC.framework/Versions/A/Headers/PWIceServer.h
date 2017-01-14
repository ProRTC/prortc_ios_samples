//
//  PWIceOptions.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWIceServer` represents a single STUN or TURN server.
 */
@interface PWIceServer : NSObject

/**
 *  @brief The URL for the ICE server.
 *
 *  @discussion Your server URL must begin with either the stun: or turn: scheme.
 *  For example, a STUN server could be defined as <stun:stun.company.com:port>.
 */
@property (nonatomic, readonly, copy) NSString *url;

/**
 *  The user name. Required for TURN servers.
 */
@property (nullable, nonatomic, readonly, copy) NSString *username;

/**
 *  The password. Required for TURN servers.
 */
@property (nullable, nonatomic, readonly, copy) NSString *password;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWIceServer cannot be created explicitly.")));

/**
 *  @brief Creates a `PWIceServer`.
 *
 *  @param serverUrl The URL for your STUN or TURN server.
 *
 *  @return A `PWIceServer` object.
 */
- (instancetype)initWithURL:(NSString *)serverUrl;

/**
 *  @brief Creates a `PWIceServer`.
 *
 *  @param serverUrl The URL for your STUN or TURN server.
 *  @param username  The username credential for your server.
 *  @param password  The password credential for your server.
 *
 *  @return A `PWIceServer` object.
 */
- (instancetype)initWithURL:(NSString *)serverUrl
                   username:(nullable NSString *)username
                   password:(nullable NSString *)password;

@end

NS_ASSUME_NONNULL_END
