//
//  PWStatsBuilder.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 
 *  `PWStatsBuilder` class used to accumulate stats information.
 */
@interface PWStatsBuilder : NSObject

/** @name CPU usage */

/** 
 *  Current CPU usage percentage.
 */
@property (nonatomic, copy, readonly, nullable) NSString *cpuUsagePercentage;


/** @name Connection stats */

/** 
 *  Estimated bitrate based on the received bytes difference over the interval between updates for this connection, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionReceivedBitrate;

/** 
 *  Formatted string of connection receive bitrate (e.g. 1 Mbps ).
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionReceivedBitrateString;

/** 
 *  Total number of bytes received for this connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionReceivedBytes;

/** 
 *  Estimated bitrate based on the sent bytes difference over the interval between updates for this connection, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionSendBitrate;

/** 
 *  Formatted string of connection send bitrate (e.g. 1 Mbps ).
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionSendBitrateString;

/** 
 *  Total number of bytes sent for this connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionSendBytes;

/** 
 *  Estimated round trip time (ms) for this connection.
 *  RTT is the length of time it takes for a signal to be sent plus the length of time it takes for an acknowledgment of that signal to be received.
 */
@property (nonatomic, copy, readonly, nullable) NSString *connectionRoundTripTime;

/** 
 *  Type of local ice candidate e.g. local or relay.
 */
@property (nonatomic, copy, readonly, nullable) NSString *localCandidateType;

/** 
 *  Type of remote ice candidate e.g. local or relay.
 */
@property (nonatomic, copy, readonly, nullable) NSString *remoteCandidateType;

/** 
 *  Transport type: UDP or TCP. TCP is usually used with TURN server.
 */
@property (nonatomic, copy, readonly, nullable) NSString *transportType;

/** 
 *  Whether connection is active or not.
 */
@property (nonatomic, copy, readonly, nullable) NSString *transportConnectionIsActive;

/** 
 *  Check if valid incoming ICE request has been received.
 */
@property (nonatomic, copy, readonly, nullable) NSString *readableIceRequest;

/** 
 *  Check if valid incoming ICE request has been received and ACK to an ICE request.
 */
@property (nonatomic, copy, readonly, nullable) NSString *writableIceRequest;

/** 
 *  Total number of RTP packets sent for this connection. Calculated as defined in [RFC3550] section 6.4.1. 
 */
@property (nonatomic, copy, readonly, nullable) NSString *packetsSent;

/** 
 *  Packets discarded on send.
 */
@property (nonatomic, copy, readonly, nullable) NSString *packetsDiscardedOnSend;

/** 
 *  It is a unique identifier that is associated to the object that was inspected to produce the RTCIceCandidateAttributes for the local candidate associated with
 *  this candidate pair.
 */
@property (nonatomic, copy, readonly, nullable) NSString *localCandidateID;

/** 
 *  It is a unique identifier that is associated to the object that was inspected to produce the RTCIceCandidateAttributes for the local candidate associated with
 *  this candidate pair. 
 */
@property (nonatomic, copy, readonly, nullable) NSString *remoteCandidateID;

/** 
 *  Local address with port, example: 192.168.2.45:63061
 */
@property (nonatomic, copy, readonly, nullable) NSString *localAddress;

/** 
 *  Remote address with port, example: 192.168.2.45:63061 
 */
@property (nonatomic, copy, readonly, nullable) NSString *remoteAddress;


/** @name Bandwidth Estimation stats */

/** 
 *  Actual encoding bitrate, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *actualEncodingBitrate;

/** 
 *  How much receive bandwidth we estimate we have, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *availableReceiveBandwidth;

/** 
 *  How much send bandwidth we estimate we have, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *availableSendBandwidth;

/** 
 *  Target encoding bitrate, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *targetEncodingBitrate;

/** 
 *  Bucket delay.
 */
@property (nonatomic, copy, readonly, nullable) NSString *bucketDelay;

/** 
 *  Retransmit bitrate, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *retransmitBitrate;

/** 
 *  The actual transmit bitrate, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *transmitBitrate;


/** @name Video send stats */

/** 
 *  Video packets lost.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendPacketsLost;

/** 
 *  Video packets send.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendPackets;

/** 
 *  Video send encode usage percent.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendEncodeUsagePercent;

/** 
 *  Video send unique identifier.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendTrackID;

/** 
 *  Average video encoding time.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendEncodeMs;

/** 
 *  Video send input frame rate.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendInputFps;

/** 
 *  Video send input height.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendInputHeight;

/** 
 *  Video send input width.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendInputWidth;

/** 
 *  Video send codec.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendCodec;

/** 
 *  Estimated bitrate based on the Video sent bytes difference over the interval between updates for this connection, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendBitrate;

/** 
 *  Formatted string of video send bitrate (e.g. 1 Mbps ).
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendBitrateString;

/** 
 *  Total number of video data (in bits) sent for this connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendBytes;

/** 
 *  Video send frames per second (FPS).
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendFps;

/** 
 *  Video send height.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendHeight;

/** 
 *  Video send width.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendWidth;

/** 
 *  Video send NACKs received.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendNacksReceived;

/** 
 *  Video send plis received.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendPlisReceived;

/** 
 *  Video send view limited resolution.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendViewLimitedResolution;

/** 
 *  Video send cpu limited resolution.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoSendCpuLimitedResolution;


/** @name Audio send stats */

/** 
 *  Estimated bitrate based on the Audio sent bytes difference over the interval between updates for this connection, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendBitrate;

/** 
 *  Formatted string of audio send bitrate (e.g. 1 Mbps ).
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendBitrateString;

/** 
 *  Total number of audio data (in bits) sent for this connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendBytes;

/** 
 *  Audio send input level
 *  You can use this property even if audio track is disabled
 *  to check if user is currently speaking/talking etc.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendInputLevel;

/** 
 *  Audio send packets lost.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendPacketsLost;

/** 
 *  Audio send packets sent.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendPackets;

/** 
 *  Audio send codec.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendCodec;

/** 
 *  Audio send track unique identifier.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendTrackID;

/** 
 *  Receive-side jitter in milliseconds.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioSendJitterReceived;


/** @name Video receive stats */

/** 
 *  Time spent decoding video in ms.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedDecodeMs;

/** 
 *  Video received decoded frames per second (FPS).
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedDecodedFps;

/** 
 *  Video received output frames per second (FPS)
 *  Real frames per second output, after processing
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedOutputFps;

/** 
 *  Video received frames per second (FPS).
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedFps;

/** 
 *  Estimated bitrate based on the Video received bytes difference over the interval between updates for this connection, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedBitrate;

/** 
 *  Formatted string of video receive bitrate (e.g. 1 Mbps ).
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedBitrateString;

/** 
 *  Total number of video data (in bits) received for this connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedBytes;

/** 
 *  Video received height.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedHeight;

/** 
 *  Video received width.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedWidth;

/** 
 *  Video packets lost.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedPacketsLost;

/** 
 *  Video packets received.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedPackets;

/** 
 *  Video receive codec.
 */
@property (nonatomic, copy, readonly, nullable) NSString *videoReceivedCodec;


/** @name Audio receive */

/** 
 *  Audio received current delay, in ms.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedCurrentDelay;

/** 
 *  Received audio packets lost.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedPacketsLost;

/** 
 *  Received audio packets number.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedPackets;

/** 
 *  Audio received track unique identifier.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedTrackId;

/** 
 *  The speech expand rate measures the amount of speech expansion done by NetEQ.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedExpandRate;

/** 
 *  Estimated bitrate based on the Audio received bytes difference over the interval between updates for this connection, bit/s.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedBitrate;

/** 
 *  Formatted string of audio receive bitrate (e.g. 1 Mbps ).
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedBitrateString;

/** 
 *  Total number of audio data (in bits) received for this connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedBytes;

/** 
 *  Received audio codec.
 */
@property (nonatomic, copy, readonly, nullable) NSString *audioReceivedCodec;

/**
 *  Developers cannot initialize this class directly.
 */
- (instancetype)init __attribute__((unavailable("PWStatsBuilder cannot be created explicitly.")));

@end

NS_ASSUME_NONNULL_END
