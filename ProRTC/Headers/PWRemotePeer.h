//
//  PWRemotePeer.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>

/**
 * The `PWRemotePeer` class represents client as a peer.
 */

@interface PWRemotePeer : NSObject

/** @name Properties */

/**
 * Peer id of client.
 */
@property (nonatomic, copy, readonly) NSString *peerId;

/**
 * Nickname of client.
 */
@property (nonatomic, copy, readonly) NSString *displayName;


/** @name Initializing */

/**
 * Initialize peer object.
 * @param peerId Client's Identifier.
 * @param displayName Client's Nickname.
 * @return Instance of `PWRemotePeer`.
 */
- (instancetype)initWithPeerId:(NSString *)peerId displayName:(NSString *)displayName;

@end
