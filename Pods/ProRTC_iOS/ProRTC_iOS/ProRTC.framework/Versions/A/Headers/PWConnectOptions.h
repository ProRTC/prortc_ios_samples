//
//  PWConnectOptions.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PWIceServer;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWConnectOptions` represents a custom configuration to use when connecting to a Room.
 *
 *  @discussion This configuration overrides default options.
 */
@interface PWConnectOptions : NSObject

/**
 *  The URL for your WebSocket server.
 */
@property (nonatomic, readonly, nullable, copy) NSString *url;

/**
 *  An array of `PWIceServer` objects to be used during connection establishment.
 */
@property (nonatomic, copy, nullable, readonly) NSArray<PWIceServer *> *servers;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWConnectOptions cannot be created explicitly.")));

/**
 *  @brief Creates a `PWConnectOptions`.
 *
 *  @param socketUrl The URL for your WebSocket server.
 *
 *  @return A `PWConnectOptions` object.
 */
- (instancetype)initWithURL:(NSString *)socketUrl;

/**
 *  @brief Creates a `PWConnectOptions`.
 *
 *  @param socketUrl The URL for your WebSocket server.
 *  @param iceServers An array of `PWIceServer` objects.
 *
 *  @return A `PWConnectOptions` object.
 */
- (instancetype)initWithURL:(NSString *)socketUrl iceServers:(NSArray<PWIceServer *> *)iceServers;

/**
 *  @brief Creates a `PWConnectOptions`.
 *
 *  @param iceServers An array of `PWIceServer` objects.
 *
 *  @return A `PWConnectOptions` object.
 */
- (instancetype)initWithIceServers:(NSArray<PWIceServer *> *)iceServers;

@end

NS_ASSUME_NONNULL_END
