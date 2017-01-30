//
//  PWMediaSession.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@class PWMediaSession;
@class PWParticipant;
@class PWLocalParticipant;
@class PWRoom;
@class PWDataFile;
@class PWStatsBuilder;
@class PWConnectOptions;
@class PWVideoTrack;
@class PWAudioTrack;

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
- (void)mediaSession:(PWMediaSession *)session didDisconnectFromRoom:(PWRoom *)room;

/**
 *  @brief This method is invoked when session fails to connect.
 *
 *  @param session The session to which connect failed.
 *  @param error The encountered error.
 */
- (void)mediaSession:(PWMediaSession *)session didFailWithError:(NSError *)error;

/**
 *  @brief This method is invoked when a participant connects to the room.
 *
 *  @param session The session in which the client is connected.
 *  @param participant The participant who connected to the room.
 */
- (void)mediaSession:(PWMediaSession *)session didJoinNewParticipant:(PWParticipant *)participant;

/**
 *  @brief This method is invoked when the participant disconnects from the room.
 *
 *  @param session The session in which the client is connected.
 *  @param participant The participant who disconnected from the room.
 */
- (void)mediaSession:(PWMediaSession *)session didDisconnectParticipant:(PWParticipant *)participant;

/**
 *  @brief This method is invoked when Participant adds video track.
 *
 *  @param session The session in which the client is connected.
 *  @param videoTrack The added video track.
 *  @param participant The participant who added the video track.
 */
- (void)mediaSession:(PWMediaSession *)session addedVideoTrack:(PWVideoTrack *)videoTrack ofParticipant:(PWParticipant *)participant;

/**
 *  @brief This method is invoked when Participant adds audio track.
 *
 *  @param session The session in which the client is connected.
 *  @param audioTrack The added audio track.
 *  @param participant The participant who added the audio track.
 */
- (void)mediaSession:(PWMediaSession *)session addedAudioTrack:(PWAudioTrack *)audioTrack ofParticipant:(PWParticipant *)participant;

/**
 *  @brief This method is invoked when session receives text-message in the room.
 *
 *  @param session The session in which the client is connected.
 *  @param message The message.
 *  @param participant The participant who sent the message.
 */
- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofParticipant:(PWParticipant *)participant;

/**
 *  @brief This method is invoked when session receives signal in the room.
 *
 *  @param session The session in which the client is connected.
 *  @param type The type of the signal.
 *  @param args The signal data.
 */
- (void)mediaSession:(PWMediaSession *)session didReceiveSignalType:(NSString *)type args:(NSDictionary *)args;

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
 *  @param participant The participant who sent the document.
 */
- (void)mediaSession:(PWMediaSession *)session didFinishReceivingDocument:(nullable PWDataFile *)document
                                                                    atURL:(NSURL *)url
                                                            ofParticipant:(PWParticipant *)participant;

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
 *  @param participant The participant whose stats session collected.
 */
- (void)mediaSession:(PWMediaSession *)session didGetStats:(PWStatsBuilder *)statsReport forParticipant:(PWParticipant *)participant;

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
 *  Represents your local Client in the Room.
 */
@property (strong, nonatomic, readonly, nullable) PWLocalParticipant *localParticipant;

/**
 *  A collection of remote participants.
 */
@property (nonatomic, copy, readonly) NSArray<PWParticipant *> *participants;

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
 *  @brief Returns the SDK version.
 *
 *  @return sdk version.
 */
+ (NSString *)version;

/**
 *  @brief Creates a `PWMediaSession`.
 *
 *  @return A `PWMediaSession` object.
 */
+ (instancetype)sharedSession;

/**
 *  @brief Connect to a Room with options.
 *
 *  @param options  The connect options.
 *  @param delegate A delegate conforming to `PWMediaSessionDelegate` for handling Room and media related events.
 */
- (void)connectWithOptions:(PWConnectOptions *)options
                  delegate:(id<PWMediaSessionDelegate>)delegate;

/**
 *  @brief Gets a Participant using sid.
 *
 *  @param sid The sid.
 *
 *  @return An instance of `PWParticipant` if successful, or `nil` if not.
 */
- (nullable PWParticipant *)getParticipantWithSid:(NSString *)sid;

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
 *  @brief Sends a signal to one or more participants in the room.
 *
 *  @param type The type of the signal.
 *  @param args The data to send. The limit to the size of data is 8KB.
 *  @param error The encountered error, If sending a signal fails.
 *  The `PWError` enum includes constants for the errors.
 *
 *  Note that success indicates that the arguments passed into the method
 *  are valid and the signal was sent. It does not indicate that the signal was
 *  sucessfully received by any of the intended recipients.
 */
- (void)signalWithType:(NSString *)type
                  args:(NSDictionary *)args
                 error:(NSError * _Nullable * _Nullable)error;

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
- (void)sendMessage:(NSString *)message
             toPeer:(NSString *)peerId;

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
- (void)sendFileData:(NSData *)data
        withFileName:(NSString *)filename
              ofType:(NSString *)extension
              toPeer:(NSString *)peerId
            streamId:(NSString *)streamId;

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
 *  @brief Disconnect session.
 */
- (void)disconnect;

@end

NS_ASSUME_NONNULL_END

