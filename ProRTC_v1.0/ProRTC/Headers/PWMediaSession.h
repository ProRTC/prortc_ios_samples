//
//  PWMediaSession.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

// prortc
#import "PWMediaConfiguration.h"

@class PWMediaSession;
@class PWRemotePeer;
@class PWRoom;
@class PWDataFile;
@class PWStatsBuilder;
@class PWMediaStream;


/**
 * `PWConnectionState` indicates the connection status B/W client and server.
 */

typedef NS_ENUM(NSInteger, PWConnectionState) {
    /**
     *  The session is not connected.
     */
    PWConnectionStateDisconnected,
    
    /**
     *  The session is connecting right now.
     */
    PWConnectionStateConnecting,
    
    /**
     *  The session is connected.
     */
    PWConnectionStateConnected,
};


/**
 * Enable/Disable 'use of datachannels'.
 * @warning If datachannels are disabled, data transfer functionality will not work.
 */
UIKIT_EXTERN void PWMediaSessionEnableDataChannels(BOOL enable);


/**
 * Used to send messages for an PWMediaSession instance. The PWMediaSession class
 * includes a
 * `delegate` property. When you send the
 * <[PWMediaSession startVideoCall:participant:displayName:delegate:]> message,
 * you specify an PWMediaSessionDelegate object.
 */

@protocol PWMediaSessionDelegate <NSObject>


@optional

/** @name Connect session */

/**
 * Sent when the client's connection state changes.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param state The <PWConnectionState> instance that represents connection state.
 */
- (void)mediaSession:(PWMediaSession *)session didChangeState:(PWConnectionState)state;


@required

/**
 * Sent when the client is successfully connected and Created/Joined Room.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param room The <PWRoom> instance of a room in which client is connected.
 */
- (void)mediaSession:(PWMediaSession *)session didConnectToRoom:(PWRoom *)room;

/**
 * Sent when the client disconnects from the session.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param room The <PWRoom> instance of a room from which client disconnects.
 */
- (void)mediaSession:(PWMediaSession *)session didDisconnectToRoom:(PWRoom *)room;

/**
 * Sent when session fails to connect.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param error A `NSError` object describing the issue. `kWebSocketErrorCode` (defined in PWTypes.h)
 * defines values for the `code` property of this object.
 */
- (void)mediaSession:(PWMediaSession *)session didFailWithError:(NSError *)error;


@optional

/** @name Room */

/**
 * Sent when the new client joins room.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param remotePeer The <PWRemotePeer> instance that represents new participant.
 */
- (void)mediaSession:(PWMediaSession *)session didJoinNewPeer:(PWRemotePeer *)remotePeer;

/**
 * Sent when the client receives list of all participants in room.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param users `NSArray` object of all participants (JSON) data.
 */
- (void)mediaSession:(PWMediaSession *)session didReceiveUsersList:(NSArray *)users;

/**
 * Sent when the other client disconnects from room.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param remotePeer The <PWRemotePeer> instance that represents participant disconnected from room.
 */
- (void)mediaSession:(PWMediaSession *)session didDisconnectPeer:(PWRemotePeer *)remotePeer;


@required

/** @name Get user media */

/**
 * Sent when client got `user-media`.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param localStream <PWMediaStream> object of webrtc local media stream interface.
 *
 * * for getting audio: <code>[localStream.audioTracks objectAtIndex:0]</code>
 * * for getting video: <code>[localStream.videoTracks objectAtIndex:0]</code>
 */
- (void)mediaSession:(PWMediaSession *)session didAddLocalStream:(PWMediaStream *)localStream;

/**
 * Sent when client got remote client `user-media`.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param remoteStream <PWMediaStream> object of webrtc remote media stream interface.
 *
 * * for getting audio: <code>[remoteStream.audioTracks objectAtIndex:0]</code>
 * * for getting video: <code>[remoteStream.videoTracks objectAtIndex:0]</code>
 * @param remotePeer The <PWRemotePeer> instance that represents remote client of incoming media.
 */
- (void)mediaSession:(PWMediaSession *)session didAddRemoteStream:(PWMediaStream *)remoteStream ofPeer:(PWRemotePeer *)remotePeer;


@optional

/** @name Text message and file share */

/**
 * Sent when client received text message, common for public/private message both.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param message `NSString` object contains text message.
 * @param remotePeer The <PWRemotePeer> sender of message.
 */
- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofPeer:(PWRemotePeer *)remotePeer;

/**
 * Sent when client is starting to receive file in chunks.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param document The <PWDataFile> object which contains all the information of incoming data.
 */
- (void)mediaSession:(PWMediaSession *)session didStartReceivingDocument:(PWDataFile *)document;

/**
 * Sent when client successfully received file.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param document The <PWDataFile> object which contains all the information of received file.
 * @param url The `NSURL` object which is a local path of received file.
 * @param remotePeer The <PWRemotePeer> sender of file.
 */
- (void)mediaSession:(PWMediaSession *)session didFinishReceivingDocument:(PWDataFile *)document atURL:(NSURL *)url ofPeer:(PWRemotePeer *)remotePeer;

/**
 * Sent when file transfer failed when connection fails.
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param error A `NSError` object describing the issue.
 * @discussion Reasons:
 *
 * * Slow internet connection.
 * * Heavy usage of bandwidth.
 * * Disconnected from server.
 * * Data channels state `close`.
 */
- (void)mediaSession:(PWMediaSession *)session didFailFileTransferWithError:(NSError *)error;


/** @name WebRTC Statistics */

/**
 * Sent on collect statistics event.
 * when you send <[PWMediaSession collectStatsWithTimeInterval:]>
 *
 * @param session The <PWMediaSession> instance that sent this message.
 * @param statsReport A `PWStatsBuilder` object describing the statistics of currently runnung connection.
 * @param remotePeer An object of remote peer W.R.T stats.
 */
- (void)mediaSession:(PWMediaSession *)session didGetStats:(PWStatsBuilder *)statsReport forPeer:(PWRemotePeer *)remotePeer;

@end


/** The `PWMediaSession` class manages the execution of WebRTC operations.
 *
 * Operations such as: handling offer/answer, ICE, renegotiation, data transfer
 * and other media activities.
 *
 * `PWMediaSession`'s delegate methods—defined by the PWMediaSessionDelegate protocol—allow
 * an object to receive callbacks regarding the success or failure of an
 * operation and Audio/Video output.
 *
 * In addition to the great communication experience, `PWMediaSession` provides support for the following features:
 *
 *  - Get statistics of running sessions.
 *  - File sharing and messaging.
 *  - Lock/Unlock feature to make room private.
 */
@interface PWMediaSession : NSObject

/** @name Properties */

/**
 * The <PWMediaSessionDelegate> object that serves as a delegate object for this
 * PWMediaSession object,
 * handling messages on behalf of this session.
 */
@property (weak, nonatomic) id <PWMediaSessionDelegate> delegate;

/**
 * The current position of your device camera.
 * `PWCameraPosition` (defined in <PWMediaConfiguration>)
 */
@property (nonatomic, assign, readonly) PWCameraPosition cameraPosition;

/**
 * Represents client oneself.
 */
@property (strong, nonatomic, readonly) PWRemotePeer *myPeer;

/**
 * Useful to identify that ongoing conference is only audio enabled (no video) or not.
 */
@property (assign, nonatomic, readonly, getter=isAudioCall) BOOL audioCall;

/**
 * To check current room is created by you OR someone else.
 */
@property (assign, nonatomic, readonly) BOOL isSelfRoomOwner;


/**
 * `onDocumentReceivingProgress` is an event responder,
 * called when file receiving progress changes.
 *
 * Use it like this:
 *
 *      <code>self.mediaSession.onDocumentReceivingProgress = ^(PWDataFile *document, float progress) {
 *
 *      };</code>
 *
 * It returns document object with its progress, you can easily identify the documents using **data_id** (defined in `PWDataFile.h`) and update the progress value.
 *
 * @return `document` - An object of PWDataFile.
 * @return `progress` - Receiving progress value of file 0 to 1.
 */
@property (nonatomic, copy) void (^onDocumentReceivingProgress)(PWDataFile *document, float progress);


/**
 * `onDocumentSendingProgress` is an event responder,
 * called when file sending progress changes.
 *
 * Use it like this:
 *
 *      <code>self.mediaSession.onDocumentSendingProgress = ^(NSString *data_id, float progress) {
 *
 *      };</code>
 *
 * It works same as `onDocumentReceivingProgress`. The only difference is: It returns **data_id** instead of document object.
 * **data_id** is the unique identifier of file transfer process. When you call <[PWMediaSession sendFileData:withFileName:ofType:toPeer:streamId:]> you have to send an unique id in `streamId` param so you can identify the operations on certain file later.
 *
 * @return `data_id` - An unique identifier of sent file.
 * @return `progress` - Receiving progress value of file 0 to 1.
 */
@property (nonatomic, copy) void (^onDocumentSendingProgress)(NSString *data_id, float progress);


/** @name Singleton */

/**
 * Singleton.
 * @return Instance of `PWMediaSession`.
 */
+ (instancetype)sharedInstance;


/** @name Initializing session */

/**
 * Start video calling
 * @param meetingId Your room name.
 * @param participantId Your unique id, can use `[NSUUID UUID].uuidString`.
 * @param displayName Your nickname, will be visible to other participants in room.
 * @param delegate The delegate (PWMediaSessionDelegate)
 */
- (void)startVideoCall:(NSString *)meetingId participant:(NSString *)participantId displayName:(NSString *)displayName delegate:(id <PWMediaSessionDelegate>)delegate;

/**
 * Start video calling with custom media configuration
 * @param meetingId Your room name.
 * @param participantId Your unique id, can use `[NSUUID UUID].uuidString`.
 * @param displayName Your nickname, will be visible to other participants in room.
 * @param delegate The delegate (PWMediaSessionDelegate)
 * @param config The configuration <PWMediaConfiguration> with custom media properties:
 *
 * * Audio/Video codecs.
 * * Camera type (front, back).
 * * Frame rate.
 * * Video dimensions.
 * * Audio/Video bandwitdh control.
 * @note By default, calculates according to device capturing capabilities.
 */
- (void)startVideoCall:(NSString *)meetingId participant:(NSString *)participantId displayName:(NSString *)displayName delegate:(id <PWMediaSessionDelegate>)delegate configuration:(PWMediaConfiguration *)config;

/**
 * Start audio calling
 * @param meetingId Your room name.
 * @param participantId Your unique id, can use `[NSUUID UUID].uuidString`.
 * @param displayName Your nickname, will be visible to other participants in room.
 * @param delegate The delegate (PWMediaSessionDelegate)
 */
- (void)startAudioCall:(NSString *)meetingId participant:(NSString *)participantId displayName:(NSString *)displayName delegate:(id <PWMediaSessionDelegate>)delegate;


/** @name Statistics */

/**
 * Get set of statistics of conections using WebRTC Apis
 * @param timeInterval A time interval, in `seconds`.
 */
- (void)collectStatsWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 * Disable timeInterval loop and stop collecting stats report.
 */
- (void)stopCollectingStats;


/** @name Text messaging */

/** 
 * Send message to all participants in room.
 * @param message Your text message.
 */
- (void)sendMessage:(NSString *)message;

/** 
 * Send private message in room.
 * @param message Your text message.
 * @param peerId `To` id (Receiver Id).
 */
- (void)sendMessage:(NSString *)message toPeer:(NSString *)peerId;


/** @name File sharing */

/**
 * Send data such as: txt, rtf, pdf and other documents.
 * @param data File in form of binary data.
 * @param filename Filename.
 * @param extension File extension.
 * @param peerId `To` id (Receiver Id).
 * @param streamId Unique identifier which represents file transfer process, can use `[NSUUID UUID].uuidString`.
 */
- (void)sendFileData:(NSData *)data withFileName:(NSString *)filename ofType:(NSString *)extension toPeer:(NSString *)peerId streamId:(NSString *)streamId;


/** @name Privacy */

/**
 * Lock room.
 * When you lock the room, no one new will be able to enter.
 * @warning Only valid for room owner.
 */
- (void)lockRoom;

/**
 * Unlock room.
 * @warning Only valid for room owner.
 */
- (void)unlockRoom;


/** @name Media */

/**
 * Switch camera.
 * @param position `PWCameraPositionBack` OR `PWCameraPositionFront`
 * defined in <PWMediaConfiguration>
 */
- (void)switchCameraPosition:(PWCameraPosition)position;

/**
 * Start publishing video.
 */
- (void)startCamera;

/**
 * Stop publishing video.
 */
- (void)stopCamera;

/**
 * Start publishing audio.
 */
- (void)startMic;

/**
 * Stop publishing audio.
 */
- (void)stopMic;

/**
 * Check video access permission is allowed by user or not.
 * @return Authorization status (`BOOL`)
 */
- (BOOL)videoAuthorized;

/**
 * Check audio access permission is allowed by user or not.
 * @return Authorization status (`BOOL`)
 */
- (BOOL)audioAuthorized;

/**
 * Use this to stop device to going in sleep mode during conferencing.
 * default is `NO`
 * @param idleTimerDisabled `BOOL`.
 * @warning Don't forget to reset it in your `End call` action or in `AppDelegate` methods `applicationDidEnterBackground` OR `applicationWillTerminate` by simply using this line of code:
 * `[[UIApplication sharedApplication] setIdleTimerDisabled:NO];`
 */
- (void)setIdleTimerDisabled:(BOOL)idleTimerDisabled;


/** @name Close session */

/**
 * End call: close all connections and purge current session.
 */
- (void)endCall;

@end
