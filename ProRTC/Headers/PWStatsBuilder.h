//
//  PWStatsBuilder.h
//  ProRTC
//
//  Copyright (c) 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>

@class RTCStatsReport;

/** 
 * Class used to accumulate stats information.
 */
@interface PWStatsBuilder : NSObject


/** @name CPU usage */

/** Current CPU usage percentage. */
@property (nonatomic, copy, readonly) NSString *cpuUsagePercentage;


/** @name Connection stats */

/** Estimated bitrate based on the received bytes difference over the interval between updates for this connection, bit/s. */
@property (nonatomic, copy, readonly) NSString *connectionReceivedBitrate;

/** Total number of bytes received for this connection. */
@property (nonatomic, copy, readonly) NSString *connectionReceivedBytes;

/** Estimated bitrate based on the sent bytes difference over the interval between updates for this connection, bit/s. */
@property (nonatomic, copy, readonly) NSString *connectionSendBitrate;

/** Total number of bytes sent for this connection. */
@property (nonatomic, copy, readonly) NSString *connectionSendBytes;

/** Estimated round trip time (ms) for this connection.
 * RTT is the length of time it takes for a signal to be sent plus the length of time it takes for an acknowledgment of that signal to be received.
 */
@property (nonatomic, copy, readonly) NSString *connectionRoundTripTime;

/** Type of local ice candidate e.g. local or relay. */
@property (nonatomic, copy, readonly) NSString *localCandidateType;

/** Type of remote ice candidate e.g. local or relay. */
@property (nonatomic, copy, readonly) NSString *remoteCandidateType;

/** Transport type: UDP or TCP. TCP is usually used with TURN server. */
@property (nonatomic, copy, readonly) NSString *transportType;

/** Whether connection is active or not. */
@property (nonatomic, copy, readonly) NSString *transportConnectionIsActive;

/** Check if valid incoming ICE request has been received. */
@property (nonatomic, copy, readonly) NSString *readableIceRequest;

/** Check if valid incoming ICE request has been received and ACK to an ICE request. */
@property (nonatomic, copy, readonly) NSString *writableIceRequest;

/** Total number of RTP packets sent for this connection. Calculated as defined in [RFC3550] section 6.4.1. */
@property (nonatomic, copy, readonly) NSString *packetsSent;

/** Packets discarded on send. */
@property (nonatomic, copy, readonly) NSString *packetsDiscardedOnSend;

/** It is a unique identifier that is associated to the object that was inspected to produce the RTCIceCandidateAttributes for the local candidate associated with this candidate pair. */
@property (nonatomic, copy, readonly) NSString *localCandidateID;

/** It is a unique identifier that is associated to the object that was inspected to produce the RTCIceCandidateAttributes for the local candidate associated with this candidate pair. */
@property (nonatomic, copy, readonly) NSString *remoteCandidateID;

/** Local address with port, example: 192.168.2.45:63061 */
@property (nonatomic, copy, readonly) NSString *localAddress;

/** Remote address with port, example: 192.168.2.45:63061 */
@property (nonatomic, copy, readonly) NSString *remoteAddress;



/** @name Bandwidth Estimation stats */

/** Actual encoding bitrate, bit/s. */
@property (nonatomic, copy, readonly) NSString *actualEncodingBitrate;

/** How much receive bandwidth we estimate we have, bit/s. */
@property (nonatomic, copy, readonly) NSString *availableReceiveBandwidth;

/** How much send bandwidth we estimate we have, bit/s. */
@property (nonatomic, copy, readonly) NSString *availableSendBandwidth;

/** Target encoding bitrate, bit/s. */
@property (nonatomic, copy, readonly) NSString *targetEncodingBitrate;

/** Bucket delay. */
@property (nonatomic, copy, readonly) NSString *bucketDelay;

/** Retransmit bitrate, bit/s. */
@property (nonatomic, copy, readonly) NSString *retransmitBitrate;

/** The actual transmit bitrate, bit/s. */
@property (nonatomic, copy, readonly) NSString *transmitBitrate;



/** @name Video send stats */

/** Video packets lost. */
@property (nonatomic, copy, readonly) NSString *videoSendPacketsLost;

/** Video packets send. */
@property (nonatomic, copy, readonly) NSString *videoSendPackets;

/** Video send encode usage percent. */
@property (nonatomic, copy, readonly) NSString *videoSendEncodeUsagePercent;

/** Video send unique identifier. */
@property (nonatomic, copy, readonly) NSString *videoSendTrackID;

/** Average video encoding time. */
@property (nonatomic, copy, readonly) NSString *videoSendEncodeMs;

/** Video send input frame rate. */
@property (nonatomic, copy, readonly) NSString *videoSendInputFps;

/** Video send input height. */
@property (nonatomic, copy, readonly) NSString *videoSendInputHeight;

/** Video send input width. */
@property (nonatomic, copy, readonly) NSString *videoSendInputWidth;

/** Video send codec: VP8 or H264. */
@property (nonatomic, copy, readonly) NSString *videoSendCodec;

/** Estimated bitrate based on the Video sent bytes difference over the interval between updates for this connection, bit/s. */
@property (nonatomic, copy, readonly) NSString *videoSendBitrate;

/** Total number of video data (in bits) sent for this connection. */
@property (nonatomic, copy, readonly) NSString *videoSendBytes;

/** Video send frames per second (FPS). */
@property (nonatomic, copy, readonly) NSString *videoSendFps;

/** Video send height. */
@property (nonatomic, copy, readonly) NSString *videoSendHeight;

/** Video send width. */
@property (nonatomic, copy, readonly) NSString *videoSendWidth;

/** Video send NACKs received. */
@property (nonatomic, copy, readonly) NSString *videoSendNacksReceived;

/** Video send plis received. */
@property (nonatomic, copy, readonly) NSString *videoSendPlisReceived;

/** Video send view limited resolution. */
@property (nonatomic, copy, readonly) NSString *videoSendViewLimitedResolution;

/** Video send cpu limited resolution. */
@property (nonatomic, copy, readonly) NSString *videoSendCpuLimitedResolution;



/** @name Audio send stats */

/** Estimated bitrate based on the Audio sent bytes difference over the interval between updates for this connection, bit/s. */
@property (nonatomic, copy, readonly) NSString *audioSendBitrate;

/** Total number of audio data (in bits) sent for this connection. */
@property (nonatomic, copy, readonly) NSString *audioSendBytes;

/** Audio send input level
 *  You can use this property even if audio track is disabled
 *  to check if user is currently speaking/talking etc.
 */
@property (nonatomic, copy, readonly) NSString *audioSendInputLevel;

/** Audio send packets lost. */
@property (nonatomic, copy, readonly) NSString *audioSendPacketsLost;

/** Audio send packets sent. */
@property (nonatomic, copy, readonly) NSString *audioSendPackets;

/** Audio send codec: OPUS, ISAC or iLBC. */
@property (nonatomic, copy, readonly) NSString *audioSendCodec;

/** Audio send track unique identifier. */
@property (nonatomic, copy, readonly) NSString *audioSendTrackID;

/** Receive-side jitter in milliseconds. */
@property (nonatomic, copy, readonly) NSString *audioSendJitterReceived;



/** @name Video receive stats */

/** Time spent decoding video in ms. */
@property (nonatomic, copy, readonly) NSString *videoReceivedDecodeMs;

/** Video received decoded frames per second (FPS). */
@property (nonatomic, copy, readonly) NSString *videoReceivedDecodedFps;

/** Video received output frames per second (FPS)
 *  Real frames per second output, after processing
 */
@property (nonatomic, copy, readonly) NSString *videoReceivedOutputFps;

/** Video received frames per second (FPS). */
@property (nonatomic, copy, readonly) NSString *videoReceivedFps;

/** Estimated bitrate based on the Video received bytes difference over the interval between updates for this connection, bit/s. */
@property (nonatomic, copy, readonly) NSString *videoReceivedBitrate;

/** Total number of video data (in bits) received for this connection. */
@property (nonatomic, copy, readonly) NSString *videoReceivedBytes;

/** Video received height. */
@property (nonatomic, copy, readonly) NSString *videoReceivedHeight;

/** Video received width. */
@property (nonatomic, copy, readonly) NSString *videoReceivedWidth;

/** Video packets lost. */
@property (nonatomic, copy, readonly) NSString *videoReceivedPacketsLost;

/** Video packets received. */
@property (nonatomic, copy, readonly) NSString *videoReceivedPackets;

/** Video receive codec: VP8 or H264. */
@property (nonatomic, copy, readonly) NSString *videoReceivedCodec;



/** @name Audio receive */

/** Audio received current delay, in ms. */
@property (nonatomic, copy, readonly) NSString *audioReceivedCurrentDelay;

/** Received audio packets lost. */
@property (nonatomic, copy, readonly) NSString *audioReceivedPacketsLost;

/** Received audio packets number. */
@property (nonatomic, copy, readonly) NSString *audioReceivedPackets;

/** Audio received track unique identifier. */
@property (nonatomic, copy, readonly) NSString *audioReceivedTrackId;

/** The speech expand rate measures the amount of speech expansion done by NetEQ. */
@property (nonatomic, copy, readonly) NSString *audioReceivedExpandRate;

/** Estimated bitrate based on the Audio received bytes difference over the interval between updates for this connection, bit/s. */
@property (nonatomic, copy, readonly) NSString *audioReceivedBitrate;

/** Total number of audio data (in bits) received for this connection. */
@property (nonatomic, copy, readonly) NSString *audioReceivedBytes;

/** Received audio codec: VP8 or H264. */
@property (nonatomic, copy, readonly) NSString *audioReceivedCodec;


/** @name Methods */

/** 
 * Parses the information in the stats report into an appropriate format.
 *
 * @param statsReport An object of `RTCStatsReport` contains WebRTC stats report data.
 */
- (void)parseStatsReport:(RTCStatsReport *)statsReport;


@end
