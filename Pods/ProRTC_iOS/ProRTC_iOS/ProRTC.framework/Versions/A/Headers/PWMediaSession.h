//
//  PWMediaSession.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

#import "PWMediaConfiguration.h"

@class PWMediaSession;
@class PWRemotePeer;
@class PWRoom;
@class PWDataFile;
@class PWStatsBuilder;
@class PWMediaStream;
@class PWConnectOptions;

/**
 * `PWConnectionState` represents the current state of session.
 */
typedef NS_ENUM(NSInteger, PWConnectionState) {
    /**
     *  The session has been disconnected.
     */
    PWConnectionStateDisconnected,
    /**
     *  The session is attempting a connection.
     */
    PWConnectionStateConnecting,
    /**
     *  The session is connected.
     */
    PWConnectionStateConnected,
};

/**
 *  @brief Enable or disable datachannels.
 *
 *  @discussion If datachannels are disabled, data transfer will not work.
 *
 *  @param enable YES or NO
 */
extern void PWMediaSessionEnableDataChannels(BOOL enable);


NS_ASSUME_NONNULL_BEGIN

/**
 *  `PWMediaSessionDelegate` provides callbacks when important changes to a `PWMediaSession` occur.
 */
@protocol PWMediaSessionDelegate <NSObject>


@optional

/**
 *  @brief This method is invoked when connection state of current session change.
 *
 *  @param session The session to which the client is attempting a connection.
 *  @param state The current state of session.
 */
- (void)mediaSession:(PWMediaSession *)session didChangeState:(PWConnectionState)state;


@required

/**
 *  @brief This method is invoked when client is successfully connected.
 *
 *  @param session The session in which the client is connected.
 *  @param room The room to which the client got connected.
 */
- (void)mediaSession:(PWMediaSession *)session didConnectToRoom:(PWRoom *)room;

/**
 *  @brief This method is invoked when the client disconnects from room.
 *
 *  @param session The session from which the client got disconnected.
 *  @param room The room from which the client got disconnected.
 */
- (void)mediaSession:(PWMediaSession *)session didDisconnectToRoom:(PWRoom *)room;

/**
 *  @brief This method is invoked when session fails to connect.
 *
 *  @param session The session to which connect failed.
 *  @param error The encountered error.
 */
- (void)mediaSession:(PWMediaSession *)session didFailWithError:(NSError *)error;


@optional

/**
 *  @brief This method is invoked when session starts establishing connection with new participant.
 *
 *  @param session The session in which the client is connected.
 *  @param remotePeer The participant who connected to the room.
 *
 *  @discussion This method is used to limit number of peers at client side.
 *
 *  @warning The implementation is not available.
 *
 *  @return If client doesn't want to process new participant, return NO. Default is YES.
 */
- (BOOL)mediaSession:(PWMediaSession *)session shouldProcessNewPeer:(PWRemotePeer *)remotePeer;

/**
 *  @brief This method is invoked when a participant connects to the room.
 *
 *  @param session The session in which the client is connected.
 *  @param remotePeer The participant who connected to the room.
 */
- (void)mediaSession:(PWMediaSession *)session didJoinNewPeer:(PWRemotePeer *)remotePeer;

/**
 *  @brief This method is invoked when the session receives list of all participants in the room.
 *
 *  @param session The session in which the client is connected.
 *  @param users An array of all participants.
 */
- (void)mediaSession:(PWMediaSession *)session didReceiveUsersList:(nullable NSArray *)users;

/**
 *  @brief This method is invoked when the participant disconnects from the room.
 *
 *  @param session The session in which the client is connected.
 *  @param remotePeer The participant who disconnected from the room.
 */
- (void)mediaSession:(PWMediaSession *)session didDisconnectPeer:(PWRemotePeer *)remotePeer;


@required

/**
 *  @brief This method is invoked when session successfully got client's local media elements.
 *
 *  @param session The session in which the client is connected.
 *  @param localStream The stream contains local media.
 *
 *  @discussion The stream contains an array of audio & video - audioTracks & videoTracks respectively.
 */
- (void)mediaSession:(PWMediaSession *)session didAddLocalStream:(PWMediaStream *)localStream;

/**
 *  @brief This method is invoked when session receives participant's media elements.
 *
 *  @param session The session in which the client is connected.
 *  @param remoteStream The stream contains participant's media.
 *  @param remotePeer The participant whose media is received.
 *
 *  @discussion The stream contains an array of audio & video - audioTracks & videoTracks respectively.
 */
- (void)mediaSession:(PWMediaSession *)session didAddRemoteStream:(PWMediaStream *)remoteStream ofPeer:(PWRemotePeer *)remotePeer;


@optional

/**
 *  @brief This method is invoked when session receives text-message in the room.
 *
 *  @param session The session in which the client is connected.
 *  @param message The message.
 *  @param remotePeer The participant who sent the message.
 */
- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofPeer:(PWRemotePeer *)remotePeer;

/**
 *  @brief This method is invoked when session starts receiving document.
 *
 *  @param session The session in which the client is connected.
 *  @param document The document which contains all the information regarding incoming data.
 *
 *  @discussion This method is only invoked when session starts receiving data in chunks.
 */
- (void)mediaSession:(PWMediaSession *)session didStartReceivingDocument:(PWDataFile *)document;

/**
 *  @brief This method is invoked when session received document successfully.
 *
 *  @param session The session in which the client is connected.
 *  @param document The document which contains all the information regarding received data.
 *  @param url The local path of received file.
 *  @param remotePeer The participant who sent the document.
 */
- (void)mediaSession:(PWMediaSession *)session didFinishReceivingDocument:(nullable PWDataFile *)document atURL:(NSURL *)url ofPeer:(PWRemotePeer *)remotePeer;

/**
 *  @brief This method is invoked when file transfer fails.
 *
 *  @param session The session in which the client is connected.
 *  @param error The encountered error.
 *
 *  @discussion Reasons could be Slow internet connection, Heavy usage of BW
 *  Session disconnected, Datachannels are disabled.
 */
- (void)mediaSession:(PWMediaSession *)session didFailFileTransferWithError:(NSError *)error;

/**
 *  @brief This method is invoked when session successfully collected stats data.
 *
 *  @param session The session in which the client is connected.
 *  @param statsReport The stats data.
 *  @param remotePeer The participant whose stats session collected.
 */
- (void)mediaSession:(PWMediaSession *)session didGetStats:(PWStatsBuilder *)statsReport forPeer:(PWRemotePeer *)remotePeer;

@end


/** 
 *  `PWMediaSession` is the root class of ProRTC framework and manages all the operations and other media activities.
 */
@interface PWMediaSession : NSObject

/**
 *  The `PWMediaSessionDelegate`. Set this property to be notified about Session and Room events such as connection status,
 *  Participants joining/leaving and local/remote media activities.
 */
@property (weak, nonatomic) id <PWMediaSessionDelegate> delegate;

/**
 *  The `PWCameraPosition`. Current position of your device camera.
 */
@property (nonatomic, assign, readonly) PWCameraPosition cameraPosition;

/**
 *  Represents client itself.
 */
@property (strong, nonatomic, readonly) PWRemotePeer *myPeer;

/**
 *  Determines that the current session is only audio or not.
 */
@property (assign, nonatomic, readonly, getter=isAudioCall) BOOL audioCall;

/**
 *  Determines that the client is Initiator.
 */
@property (assign, nonatomic, readonly) BOOL isSelfRoomOwner;

/**
 *  Total number of connections that are connected or in process.
 */
@property (assign, nonatomic, readonly) NSUInteger connectionsCount;

/**
 *  This is an event responder,
 *  called when document receiving progress changes.
 */
@property (nonatomic, copy) void (^onDocumentReceivingProgress)(PWDataFile *document, float progress);

/**
 *  This is an event responder,
 *  called when document sending progress changes.
 */
@property (nonatomic, copy) void (^onDocumentSendingProgress)(NSString *data_id, float progress);

/**
 *  @brief Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWMediaSession cannot be created explicitly.")));

/**
 *  @brief Creates a `PWMediaSession`.
 *
 *  @return A `PWMediaSession` object.
 */
+ (instancetype)sharedSession;

/**
 *  @brief Creates a `PWMediaSession`.
 *
 *  @param options The connect options.
 *
 *  @return A `PWMediaSession` object.
 */
+ (instancetype)sharedSessionWithOptions:(nullable PWConnectOptions *)options;

/**
 *  @brief Method to initialize video call.
 *
 *  @param meetingId The room Id.
 *  @param displayName The name that will be visible to other participants in the room.
 *  @param delegate A delegate conforming to `PWMediaSessionDelegate` for handling Room/Session related events.
 */
- (void)startVideoCall:(NSString *)meetingId displayName:(NSString *)displayName delegate:(id <PWMediaSessionDelegate>)delegate;

/**
 *  @brief Method to initialize video call with custom media configuration.
 *
 *  @param meetingId The room Id.
 *  @param displayName The name that will be visible to other participants in the room.
 *  @param delegate A delegate conforming to `PWMediaSessionDelegate` for handling Room/Session related events.
 *  @param config The `PWMediaConfiguration`. Configuration with custom values:
 *
 *  @discussion By default, use configuration based on device capabilities.
 */
- (void)startVideoCall:(NSString *)meetingId displayName:(NSString *)displayName delegate:(id <PWMediaSessionDelegate>)delegate configuration:(nullable PWMediaConfiguration *)config;

/**
 *  @brief Method to initialize audio call.
 *
 *  @param meetingId The room Id.
 *  @param displayName The name that will be visible to other participants in the room.
 *  @param delegate A delegate conforming to `PWMediaSessionDelegate` for handling Room/Session related events.
 */
- (void)startAudioCall:(NSString *)meetingId displayName:(NSString *)displayName delegate:(id <PWMediaSessionDelegate>)delegate;

/**
 *  @brief Get stats data of conections in a given time interval.
 *
 *  @param timeInterval The time interval in seconds.
 */
- (void)collectStatsWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 *  @brief Stop collecting stats data.
 */
- (void)stopCollectingStats;

/** 
 *  @brief Send message to all participants in the room.
 *
 *  @param message The message.
 */
- (void)sendMessage:(NSString *)message;

/** 
 *  @brief Send private message in the room.
 *
 *  @param message The message.
 *  @param peerId Recipient Id.
 */
- (void)sendMessage:(NSString *)message toPeer:(NSString *)peerId;

/**
 *  @brief Method to transfer data.
 *
 *  @param data The binary data of file.
 *  @param filename The name of file.
 *  @param extension The extension of file.
 *  @param peerId Recipient Id.
 *  @param streamId An unique identifier which represents file transfer process, use UUID.
 *
 *  @discussion This method requires datachannels to be enabled.
 */
- (void)sendFileData:(NSData *)data withFileName:(NSString *)filename ofType:(NSString *)extension toPeer:(NSString *)peerId streamId:(NSString *)streamId;

/**
 *  @brief Lock room, new participants cannot enter in the room.
 *
 *  @warning The implementation is not available.
 */
- (void)lockRoom;

/**
 *  @brief Unlock room, new participants can enter in the room.
 *
 *  @warning The implementation is not available.
 */
- (void)unlockRoom;

/**
 *  @brief Switch camera position.
 *
 *  @param position The `PWCameraPosition`.
 */
- (void)switchCameraPosition:(PWCameraPosition)position;

/**
 *  @brief Start publishing video.
 */
- (void)startCamera;

/**
 *  @brief Stop publishing video.
 */
- (void)stopCamera;

/**
 *  @brief Start publishing audio.
 */
- (void)startMic;

/**
 *  @brief Stop publishing audio.
 */
- (void)stopMic;

/**
 *  @brief Check video access permission is allowed by user.
 *
 *  @return Authorization status.
 */
- (BOOL)videoAuthorized;

/**
 *  @brief Check audio access permission is allowed by user.
 *
 *  @return Authorization status.
 */
- (BOOL)audioAuthorized;

/**
 *  @brief Stop device to go into sleep mode during call. Default is NO.
 *
 *  @param idleTimerDisabled YES or NO.
 *
 *  @warning Don't forget to reset it in your End-call action.
 */
- (void)setIdleTimerDisabled:(BOOL)idleTimerDisabled;

/**
 *  @brief Initialize SSL.
 */
- (void)initializeSSL;

/**
 *  @brief Clean-up SSL.
 */
- (void)cleanupSSL;

/**
 *  @brief End call.
 */
- (void)endCall;

@end

NS_ASSUME_NONNULL_END

