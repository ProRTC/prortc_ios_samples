<br>
<p align="center" >
<a href="http://prortc.com/">
  <img src="ProRTC_logo.png" height="101" alt="ProRTC" title="ProRTC">
</a>
</p>
<br>
# ProRTC iOS Sample - A WebRTC Solution for iOS

[![Version](https://img.shields.io/cocoapods/v/ProRTC_iOS.svg?style=flat)](https://github.com/ProRTC/ProRTC_iOS)
[![Platform](https://img.shields.io/cocoapods/p/ProRTC_iOS.svg?style=flat)]()
[![Twitter](https://img.shields.io/badge/twitter-@ProRTC-55acee.svg?style=flat)](http://twitter.com/ProRTCApp)
[![Facebook](https://img.shields.io/badge/facebook-@ProRTC-3b5998.svg?style=flat)](https://www.facebook.com/Prortcapp-999509483500735/)
[![Google](https://img.shields.io/badge/google+-@ProRTC-dd4b39.svg?style=flat)](https://plus.google.com/+CodiantInc)
[![LinkedIn](https://img.shields.io/badge/linkedin-@ProRTC-0077b5.svg?style=flat)](https://www.linkedin.com/company/neuron-solutions-inc-)

ProRTC framework provides the infrastructure needed to integrate Google native WebRTC in iOS apps. 
It is a layer handcrafted over WebRTC native trunk code to obtain audio/video conferencing, text-chat, file sharing and other cool stuff.

ProRTC iOS sample helps you to better understand the features of ProRTC and demonstrates basic integration steps for providing support for the following features in your iPhone/iPad apps:

 - 4-way voice and video call.
 - Text-chat.
 - Datachannels support.

# If you have any feedback, doubts or feature request, feel free to email us at support@prortc.com

# How To Get Started

- [Download ProRTC](http://prortc.com/) and try out the included sample project.
- Check out the [documentation](http://prortc.com/document/) for the APIs available in ProRTC framework.

# Installation

The ProRTC requires **Xcode 7+**.

## CocoaPods

[CocoaPods](http://cocoapods.org) is a dependency manager for Objective-C, which simplifies the process of integrating 3rd-party libraries in your projects. You can install it with the following command:

```bash
$ gem install cocoapods
```

#### Podfile

To integrate ProRTC into your Xcode project using CocoaPods, specify it in your `Podfile`:

```ruby
platform :ios, '9.0'

target 'TargetName' do
pod 'ProRTC_iOS'
end
```

Then, run the following command:

```bash
$ pod install
```

## Manually

Drag & drop `ProRTC.framework` into your project. If you don't have `ProRTC.framework`, you can download from [here](http://prortc.com/) Or you can easily find in this sample project.

The ProRTC framework requires the following frameworks and libraries:
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

Goto your project **Build settings** and add **-ObjC** flag in **Other linker flag** section.

### All done!

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
- `PWLocalCameraPreview`
- `PWVideoTrack`
- `PWStatsBuilder`
- `PWIceServer`
- `PWConnectOptions`
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
- `PWVideoCapturePreset`
- `PWVideoCodec`
- `PWErrorCode`

# Usage

Before getting started, let’s discuss some of the most important classes you’ll be using in this project:

### PWMediaSession
`PWMediaSession` is the root class of ProRTC framework, manages all the operations and other media activities.

`PWMediaSession’s` delegate methods—defined by the `PWMediaSessionDelegate` protocol—allow an object to receive callbacks regarding the success or failure of an operation.

### PWMediaConfiguration
The `PWMediaConfiguration` class manages Media related configuration.

`PWMediaConfiguration` provides interface for the following:

- Audio/Video codecs. (Supported formats: H.264, VP8, Opus)
- Audio/Video bandwidth control.
- Video capture presets.
- Computes preferred receiving video format on the basis of device capabilities and performance.

### Initialization

Import ProRTC.framework header file:
```objective-c
#import <ProRTC/ProRTC.h>
```

`PWMediaSession` is the main class used to perform WebRTC operations. Your class must conforms its protocol `PWMediaSessionDelegate`.

```objective-c
@interface ViewController () <PWMediaSessionDelegate>

@end
```

`PWMediaSessionDelegate` - Handles events such as participant joining/leaving, connect/disconnect states and local/remote media.

Create a property of `PWMediaSession`, using this session you'll be doing all WebRTC operations.
```objective-c
@property (strong, nonatomic) PWMediaSession *mediaSession;
```

####• Get User Media

`PWLocalCameraPreview` class is used for displaying local camera video.

`PWEAGLVideoView` is used for rendering remote participant's video.

Create two properties:
- One for `Remote`.
- One for `Local`.

You can also use `storyboard`, create two simple `UIView`'s and set Custom class.

```objective-c
// remoteVideoView: An object of PWEAGLVideoView to show remote video.
@property (weak, nonatomic) IBOutlet PWEAGLVideoView *remoteVideoView;

// localVideoView: An object of PWLocalCameraPreview to show local camera video.
@property (weak, nonatomic) IBOutlet PWLocalCameraPreview *localVideoView;
```

For handling received video data - create properties of `PWVideoTrack`: 

```objective-c
// PWVideoTrack objects to hold local and remote videos data.
@property (strong, nonatomic) PWVideoTrack *localVideoTrack;
@property (strong, nonatomic) PWVideoTrack *remoteVideoTrack;
```
####• Video Call

```objective-c
// Initialize session.
self.mediaSession = [PWMediaSession sharedSession];

// Start video call.
// @param: room Id or Meeting Id.
// @param: participant name --
// @param: delegate <PWMediaSessionDelegate>

NSString *name = [UIDevice currentDevice].name;
NSString *meetingId = @"prortc";

[self.mediaSession startVideoCall:meetingId displayName:name delegate:self];

```
####• Video call with custom media configuration:

You can change these properties according to your requirement. If you do not - By default best configuration will be used.

For more details: see [`PWMediaConfiguration.h`](http://prortc.com/document/Classes/PWMediaConfiguration.html)

```objective-c
//
// Default media configuration:
//
// Audio codec: Opus
// Audio bandiwidth limit: 120000 // 120 Kbps
// Video codec: H.264
// Video bandwidth limit: 1.5e6 // 1.5 Mbps
// Video capture preset: PWVideoCapturePreset640x480 // 4:3 output (640x480)
// Camera position: front
//

NSString *name = [UIDevice currentDevice].name;
NSString *meetingId = @"prortc";

PWMediaConfiguration *config = [PWMediaConfiguration defaultConfiguration];
// Change the configuration here, If needed...
// e.g.
config.maxVideoBitrate = 1.8e6; // extends video bitrate from 1.5 Mbps to 1.8 Mbps.
[self.mediaSession startVideoCall:meetingId displayName:name delegate:self configuration:config];

```
<br>
<b>• Audio only call:</b>
```objective-c
NSString *name = [UIDevice currentDevice].name;
NSString *meetingId = @"prortc";

[self.mediaSession startAudioCall:meetingId displayName:name delegate:self];
```
### Delegates

####• Connection state:
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

####• Audio/Video:
```objective-c
- (void)mediaSession:(PWMediaSession *)session didAddLocalStream:(PWMediaStream *)localStream
{
    // No need of rendering in case of audio conferencing.
    if (localStream.isVideoTrackAvailable) {
        
        // save video track of media stream.
        self.localVideoTrack = localStream.videoTracks[0];
        
        // start rendering of local camera video.
        [self.localVideoView bindWithLocalVideoTrack:self.localVideoTrack];
    }
}

- (void)mediaSession:(PWMediaSession *)session didAddRemoteStream:(PWMediaStream *)remoteStream ofPeer:(PWRemotePeer *)remotePeer
{
    // No need of rendering in case of audio conferencing.
    if (remoteStream.isVideoTrackAvailable) {
        
        // save video track of media stream.
        self.remoteVideoTrack = remoteStream.videoTracks[0];
        
        // start rendering of remote camera video.
        [self.remoteVideoView bindTrack:self.remoteVideoTrack];
    }
}
```

####• Failure:
```objective-c
- (void)mediaSession:(PWMediaSession *)session didFailWithError:(NSError *)error
{
    // For performing different operations on different error.
    // @See: PWErrorCode (defined in PWErrorCode.h)
}
```

### Text-chat

#### Sending Text message to all participants in the room
```objective-c
[self.mediaSession sendMessage:message];
```

#### Sending Text message to single participant in the room: Private
```objective-c
[self.mediaSession sendMessage:message toPeer:<recipient_id>];
```

#### Delegates
Called when `session` receives new Text message in room (Common for both public/private messages).
```objective-c
- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofPeer:(PWRemotePeer *)remotePeer
{
    // message: text message.
    // remotePeer: sender of message.
}
```
<br>

### Extras

####• To check Audio/Video access permission

```objective-c
if (self.mediaSession.videoAuthorized) {

}

if (self.mediaSession.audioAuthorized) {

}
```

####• Stop device to go into sleep mode during call

```objective-c
// default is `NO`
[self.mediaSession setIdleTimerDisabled:YES];
```
Don't forget to reset it in your `End call` action or in `AppDelegate` method `applicationWillTerminate` by simply using this line of code:
 * `[[UIApplication sharedApplication] setIdleTimerDisabled:NO];` OR
 * `[self.mediaSession setIdleTimerDisabled:NO];`
 
####• Switching Camera

```objective-c
if (self.mediaSession.cameraPosition == PWCameraPositionFront) {
    [self.mediaSession switchCameraPosition:PWCameraPositionBack];
}
else {
      [self.mediaSession switchCameraPosition:PWCameraPositionFront];
}
```

####• Mute/UnMute Audio/Video

```objective-c
[self.mediaSession stopMic];
[self.mediaSession startMic];

[self.mediaSession stopCamera];
[self.mediaSession startCamera];
```

For More Details: See [`PWMediaSession.h`](http://prortc.com/document/Classes/PWMediaSession.html)

## Contributing
If you want to contribute in WebRTC era, share your ideas, changes and modifications to provide more benefits to developers.

## Known Issues
None at this time.

## Author
[Codiant Software Technology Pvt Ltd](http://www.codiant.com) develops and operates ProRTC.
<br><br>
ProRTC project authors, support@prortc.com

## Changelog
### See [Changelog.md](https://github.com/ProRTC/prortc_ios_samples/blob/master/CHANGELOG.md)

## License
You're free to copy and modify the source code of ProRTC sample project for your own projects. See LICENSE for details.
<br><br>
ProRTC services are available under the Commercial license. See the [Terms](http://prortc.com/terms-conditions.php) for more info.
<br><br>
The ProRTC framework utilizes the following copyrighted projects, the use of which is hereby acknowledged.
* [WebRTC](https://chromium.googlesource.com/external/webrtc/+/master/webrtc/LICENSE)

# If you have any feedback, doubts or feature request, feel free to email us at support@prortc.com
