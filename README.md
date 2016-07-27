<br>
<p align="center" >
  <img src="ProRTC_logo.png" height="101" alt="ProRTC" title="ProRTC">
</p>
<br>
# ProRTC iOS Sample - A WebRTC Solution for iOS

ProRTC library provides the infrastructure needed to integrate Google native WebRTC in iOS apps. 
It is a layer handcrafted over WebRTC native trunk code to obtain audio/video conferencing, text-chat, file sharing and other cool stuff.

ProRTC iOS sample helps you to better understand the features of ProRTC library and demonstrates basic integration steps for providing support for the following features in your iPhone/iPad apps:

 - 1x1 Video conferencing.
 - Text messaging.
 - Data channels support.

# If you have any feedback, doubts or feature request, feel free to email us at support@prortc.com

# Project Setup

The ProRTC library requires **Xcode 7+**.

Import ProRTC library folder into your project which contains:
* libProRTCCore.a
* libProRTC.a
* Headers

You can easily find these files in this sample project.

The ProRTC library requires the following frameworks and libraries:
* UIKit.framework
* GLKit.framework
* CoreMedia.framework
* CoreGraphics.framework
* CoreVideo.framework
* AVFoundation.framework
* Foundation.framework
* Security.framework
* CFNetwork.framework
* AudioToolbox.framework
* VideoToolbox.framework
* CoreVideo.framework
* CoreAudio.framework
* OpenGLES.framework
* QuartzCore.framework
* libsqlite3.dylib
* libSystem.B.dylib
* libstdc++.6.0.9.dylib
* libicucore.A.dylib
* libc++.1.dylib

**Final step: Other linker flag**

**libProRTC.a** includes few Objective-C categories of **WebRTC** classes so we need to make sure that linker loads all categories and classes of static library properly:

Goto your project **Build settings** and add **-ObjC** flag in **Other linker flag** section.

### All done! 😎

# Requirements

**BUILD REQUIREMENTS:**

iOS SDK 9.0 or later

**RUNTIME REQUIREMENTS:**

iOS 9.0 or later

Supported on **Wi-Fi** and **3G/4G/LTE** connections.

# Architecture

### Class References
- `PWMediaSession`
- `PWMediaStream`
- `PWEAGLVideoView`
- `PWVideoTrack`
- `PWStatsBuilder`
- `PWMediaConfiguration`
- `PWDataFile`
- `PWRemotePeer`
- `PWRoom`

### Protocol References
- `PWMediaSessionDelegate`

### Constant References
- `PWAudioCodec`
- `PWCameraPosition`
- `PWConnectionState`
- `PWPixelFormat`
- `PWRendererType`
- `PWVideoCodec`
- `kWebSocketErrorCode`

# Usage

Before getting started, let’s discuss some of the most important classes you’ll be using in this project:

### PWMediaSession
The `PWMediaSession` class manages the execution of WebRTC operations such as: handling `offer/answer`, `ICE`, renegotiation, data transfer and other media activities.

`PWMediaSession’s` delegate methods—defined by the `PWMediaSessionDelegate` protocol—allow an object to receive callbacks regarding the success or failure of an operation.

### PWMediaConfiguration
The `PWMediaConfiguration` class manages Media properties and configuration.

`PWMediaConfiguration` provides support for the following features:

- Rendering.
- Audio/Video codecs.
- Audio/Video bandwidth control.
- Frame rate & pixel formats.
- Computes preferred receiving video format on the basis of device capabilities and performance.

### Initialization

Import ProRTC library header file:
```objective-c
#import "ProRTC.h"
```

`PWMediaSession` is the main class used to perform WebRTC operations. Your class must conforms its protocol `PWMediaSessionDelegate`.

```objective-c
@interface ViewController () <PWMediaSessionDelegate>

@end
```

* `PWMediaSessionDelegate` - Handles events when remote client connects and disconnect states. Also, handles events when local and remote video feeds are received.

Create a property of `PWMediaSession`, using this session you'll be doing all WebRTC operations.
```objective-c
@property (strong, nonatomic) PWMediaSession *mediaSession;
```

### Rendering

`PWEAGLVideoView` is used for rendering of Local and Remote videos so create two properties of `PWEAGLVideoView`.
- One for `Remote`.
- One for `Local`.

You can also use `storyboard`, create two simple `UIView`'s and set `PWEAGLVideoView` as a `Custom class`.

```objective-c
// remoteVideoView: An object of PWEAGLVideoView to show remote video.
@property (weak, nonatomic) IBOutlet PWEAGLVideoView *remoteVideoView;

// localVideoView: An object of PWEAGLVideoView to show local camera video.
@property (weak, nonatomic) IBOutlet PWEAGLVideoView *localVideoView;
```

For handling received media data - create properties of `PWVideoTrack`: 

```objective-c
// PWVideoTrack objects to hold local and remote videos data.
@property (strong, nonatomic) PWVideoTrack *localVideoTrack;
@property (strong, nonatomic) PWVideoTrack *remoteVideoTrack;
```
### Go Live

```objective-c
// Initialize session.
self.mediaSession = [PWMediaSession sharedInstance];

// Start video call.
// @param: room name or any unique identifier.
// @param: participant id --
// @param: participant name --
// @param: delegate <PWMediaSessionDelegate>
//
// It's just a sample and we're not maintaining user data so [NSUUID UUID] is a best option for unique id of participant.
// You can pass your own values If you want.
//
    
NSString *GUID = [NSUUID UUID].UUIDString;
NSString *name = [UIDevice currentDevice].name;
    
[self.mediaSession startVideoCall:self.roomName participant:GUID displayName:name delegate:self];

```
<br>
<b>Video call with custom media configuration:</b>
You can change these properties according to your requirement. If you do not - By default best configuration will be used.

For more details: see `PWMediaConfiguration.h`

```objective-c
//
// Default media configuration:
//
// Audio codec: Opus audio codec (good quality)
// Audio bandiwidth limit: 64
// Video codec: Software (VP8)
// Video renderer: OpenGLES 2.0
// Video bandwidth limit: 512 // must be greater than 300, If you really want to see other participant's face. :P
// Video format: 640 x 480
// Frame rate: @30 // varies according to the device performance.
// Camera position: front
//
PWMediaConfiguration *config = [PWMediaConfiguration defaultConfiguration];

[self.mediaSession startVideoCall:self.roomName participant:GUID displayName:name delegate:self configuration:config];

```
<br>
<b>For Audio only call:</b>
```objective-c
[self.mediaSession startAudioCall:self.roomName participant:GUID displayName:name delegate:self];
```
### Delegates

<b>Connection state:</b>
```objective-c
- (void)mediaSession:(PWMediaSession *)session didChangeState:(PWConnectionState)state
{
    switch (state) {
        case PWConnectionStateConnecting:
            // connecting...
            break;
        case PWConnectionStateConnected:
            // connected...
            break;
        case PWConnectionStateDisconnected:
            // disconnected...
            break;
        default:
            break;
    }
}

- (void)mediaSession:(PWMediaSession *)session didConnectToRoom:(PWRoom *)room
{
    // successfully connected to room...
}
```

<b>A/V:</b>
```objective-c
- (void)mediaSession:(PWMediaSession *)session didAddLocalStream:(PWMediaStream *)localStream
{
    // No need of rendering in case of audio conferencing.
    if (localStream.isVideoTrackAvailable) {
        
        // save video track of media stream.
        self.localVideoTrack = localStream.videoTracks[0];
        
        // start rendering of local camera video.
        [self.localVideoTrack bindRendererView:self.localVideoView];
    }
}

- (void)mediaSession:(PWMediaSession *)session didAddRemoteStream:(PWMediaStream *)remoteStream ofPeer:(PWRemotePeer *)remotePeer
{
    // No need of rendering in case of audio conferencing.
    if (remoteStream.isVideoTrackAvailable) {
        
        // save video track of media stream.
        self.remoteVideoTrack = remoteStream.videoTracks[0];
        
        // start rendering of remote camera video.
        [self.remoteVideoTrack bindRendererView:self.remoteVideoView];
    }
}
```

<b>Failure:</b>
```objective-c
- (void)mediaSession:(PWMediaSession *)session didFailWithError:(NSError *)error
{
    // For performing different operations on different error.
    // @See: kWebSocketErrorCode (defined in PWTypes.h)
}
```

### ⭐ Text messaging and Data transfer

<b>ProRTC</b> uses `Data Channels` for transferring any type of data, with the help of datachannels you can transfer files or even you can also send text messages.
If datachannels are not enabled, file sharing will not work but text messaging will.
By default session checks, If datachannels are enabled private messages will be sent through channels not server.
If disabled, messages will be sent through server.

You can use this feature by simply adding one line of code 😉

```objective-c
PWMediaSessionEnableDataChannels(YES);
```
<b>NOTE:</b> This line of code must be written before initiating call. Do not forget to disable it, if not using, It'll save processing time.

File transfer is a very important and little bit complex part of communication. In <b>ProRTC</b> we've focused on so many points to make this feature easy to integrate.

Developers want to know everything:
- When file sending process started.
- How much data is sent or received.
- When file receiving process finished and much more.

So we've provided functions and properties to handle this giant process. We're regularly working on this to make it more simpler but as of now lets see what we have:

<br>
<b>Sending Text message</b>
```objective-c
[self.mediaSession sendMessage:message.text toPeer:<recipient_id>];
```

<b>Sending file</b>
```objective-c
[self.mediaSession sendFileData:<NSData> withFileName:<fileName> ofType:<fileExt> toPeer:<recipient_id> streamId:[NSUUID UUID].UUIDString];
```
<b>NOTE:</b> If `Data channels` are not enabled, this method won't work.
<br><b>PERFORMANCE:</b> Sending large files requires great Internet speed. Keep it in mind if network speed is slow do not try to send large files OR multiple files at the same time, It'll degrade your video call performance. If not using <b>Wi-Fi</b>: data charges may apply.

<br>
### Delegates
<b>Called when `session` receives new Text message in room (Common for both public/private messages)</b>
```objective-c
- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofPeer:(PWRemotePeer *)remotePeer
{
    // message: text message.
    // remotePeer: sender of message.
}
```
<br>
<b>Called only once when `session` starts receiving new file</b> - `PWDataFile` object holds all the information of incoming file.
Each file transfer process is represented by unique identifier `data_id` (defined in `PWDataFile.h`), you can use this `data_id` to identify which operation is for which file.
```objective-c
- (void)mediaSession:(PWMediaSession *)session didStartReceivingDocument:(PWDataFile *)document
{

}
```
<b>NOTE:</b> In this delegate, you may not be able to get few details of file because file is not received yet!

<br>
<b>Called when `session` successfully received file</b>

```objective-c
- (void)mediaSession:(PWMediaSession *)session didFinishReceivingDocument:(PWDataFile *)document atURL:(NSURL *)url ofPeer:(PWRemotePeer *)remotePeer
{
  // document: object of received file.
  // url: path of document directory where received file is saved.
  // remotePeer: sender of file.
}
```
<br>
<b>Sending/Receiving Progress: This is a big one 😃</b>
Above two delegate tells about start/finish but what about the scene in between, don't worry we have functions for this too 😉

<b>Receiving progress</b>

For getting file receiving progress, add this property block - Callback when file receiving progress changes.

```objective-c
self.mediaSession.onDocumentReceivingProgress = ^ (PWDataFile *document, float progress) {
    // find your file object using predicate or some other way 
    // which you've saved previously in <didStartReceivingDocument> method.
    // update progress.
};
```

<b>Sending progress</b>

For getting file sending progress, add this property block - Callback when file sending progress changes.

```objective-c
self.mediaSession.onDocumentSendingProgress = ^(NSString *data_id, float progress) {
    
};
```
<b>NOTE:</b> This block doesn't return `PWDataFile` object because you're the sender and you should have all the information about your file. It only tells you how much data you've sent and how much is remaining.
<br>
### Extras 😎

<b>To check Audio/Video access permission</b>

```objective-c
if (self.mediaSession.videoAuthorized) {

}

if (self.mediaSession.audioAuthorized) {

}
```

<b>Use this to stop device to going in sleep mode during conferencing</b>
<br>default is `NO`

```objective-c
[self.mediaSession setIdleTimerDisabled:YES];
```
Don't forget to reset it in your `End call` action or in `AppDelegate` methods `applicationDidEnterBackground` OR `applicationWillTerminate` by simply using this line of code:
 * `[[UIApplication sharedApplication] setIdleTimerDisabled:NO];` OR
 * `[self.mediaSession setIdleTimerDisabled:NO];`
 
<b>Switching Camera</b>

```objective-c
if (self.mediaSession.cameraPosition == PWCameraPositionFront) {
    [self.mediaSession switchCameraPosition:PWCameraPositionBack];
}
else {
      [self.mediaSession switchCameraPosition:PWCameraPositionFront];
}
```

<b>Mute/UnMute A/V</b>

```objective-c
[self.mediaSession stopMic];
[self.mediaSession startMic];

[self.mediaSession stopCamera];
[self.mediaSession startCamera];
```

<br>
<b>For More Details: See `PWMediaSession.h`</b>

## Contributing
If you want to contribute in WebRTC era, share your ideas, changes and modifications to provide more benefits to developers.

## 🔧 Known Issues
None at this time.

## 👑 Author
[Codiant Software Technology Pvt Ltd](http://www.codiant.com).

## 📄 Change Log
### See [Changelog.md](https://github.com/ProRTC/prortc_ios_samples/blob/master/CHANGELOG.md)

## License
You're free to copy and modify the source code of ProRTC sample project for your own projects. See LICENSE for details.

# If you have any feedback, doubts or feature request, feel free to email us at support@prortc.com
