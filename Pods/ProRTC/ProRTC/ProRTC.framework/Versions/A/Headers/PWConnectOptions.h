//
//  PWConnectOptions.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PWIceServer;
@class PWLocalMedia;

NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWConnectOptionsBuilder` constructs `PWConnectOptions`.
 */
@interface PWConnectOptionsBuilder : NSObject

/**
 *  @brief The URL for your WebSocket server. Default is nil and communication will be
 *  handled by ProRTC servers.
 *
 *  @discussion It is possible to change web-socket URL to deploy communication through your own server,
 *  For more details: https://prortc.com/contact-us.php
 */
@property (nonatomic, strong, nullable) NSString *url;

/**
 *  @brief An array of `PWIceServer` objects to be used during connection establishment.
 *  Default is nil and media relaying will be handled by ProRTC Ice servers.
 */
@property (nonatomic, strong, nullable) NSArray<PWIceServer *> *servers;

/**
 *  @brief The name of the room in which you want to connect.
 */
@property (nonatomic, strong) NSString *name;

/**
 *  @brief The name of the participant who connects in the room. Default is nil.
 *
 *  @discussion This name will be shared with other participants in the room.
 */
@property (nonatomic, strong, nullable) NSString *participantName;

/**
 *  @brief The media of your device.
 *
 *  @discussion This local media will be shared with other participants in the room.
 */
@property (nonatomic, strong) PWLocalMedia *localMedia;

/**
 *  @brief Indicates If the data-channel is enabled. Default is NO.
 */
@property (nonatomic, assign) BOOL enableDataChannel;

@end

/**
 *  `PWConnectOptions` represents a custom configuration to use when connecting to a Room.
 */
@interface PWConnectOptions : NSObject

/**
 *  @brief The URL for your WebSocket server. Default is nil and communication will be
 *  handled by ProRTC servers.
 *
 *  @discussion It is possible to change web-socket URL to deploy communication through your own server,
 *  For more details: https://prortc.com/contact-us.php
 */
@property (nonatomic, readonly, copy, nullable) NSString *url;

/**
 *  @brief An array of `PWIceServer` objects to be used during connection establishment.
 *  Default is nil and media relaying will be handled by ProRTC Ice servers.
 */
@property (nonatomic, readonly, strong, nullable) NSArray<PWIceServer *> *servers;

/**
 *  @brief The name of the room in which you want to connect.
 */
@property (nonatomic, readonly, copy) NSString *name;

/**
 *  @brief The name of the participant who connects in the room. Default is nil.
 *
 *  @discussion This name will be shared with other participants in the room.
 */
@property (nonatomic, readonly, copy, nullable) NSString *participantName;

/**
 *  @brief The media of your device.
 *
 *  @discussion This local media will be shared with other participants in the room.
 */
@property (nonatomic, readonly, strong) PWLocalMedia *localMedia;

/**
 *  @brief Indicates If the data-channel is enabled. Default is NO.
 */
@property (nonatomic, readonly, assign, getter=isEnabledDataChannel) BOOL enableDataChannel;

/**
 *  @brief Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWConnectOptions cannot be created explicitly.")));

/**
 *  @brief Creates a `PWConnectOptions`.
 *
 *  @param builder The connect options.
 *
 *  @return A `PWConnectOptions` object.
 */
- (instancetype)initWithBuilder:(PWConnectOptionsBuilder *)builder;

@end

NS_ASSUME_NONNULL_END
