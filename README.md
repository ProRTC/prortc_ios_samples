<br>
<p align="center" >
<a href="https://prortc.com/">
  <img src="ProRTC_logo.png" height="101" alt="ProRTC" title="ProRTC">
</a>
</p>
<br>
# ProRTC iOS Sample - A WebRTC Solution for iOS

[![Version](https://img.shields.io/cocoapods/v/ProRTC.svg?style=flat)](http://cocoapods.org/pods/ProRTC)
[![Platform](https://img.shields.io/cocoapods/p/ProRTC.svg?style=flat)](http://cocoapods.org/pods/ProRTC)
[![Twitter](https://img.shields.io/badge/twitter-@ProRTC-55acee.svg?style=flat)](http://twitter.com/ProRTCApp)
[![Facebook](https://img.shields.io/badge/facebook-@ProRTC-3b5998.svg?style=flat)](https://www.facebook.com/Prortcapp-999509483500735/)
[![Google](https://img.shields.io/badge/google+-@ProRTC-dd4b39.svg?style=flat)](https://plus.google.com/+CodiantInc)
[![LinkedIn](https://img.shields.io/badge/linkedin-@ProRTC-0077b5.svg?style=flat)](https://www.linkedin.com/company/neuron-solutions-inc-)

ProRTC framework provides the infrastructure needed to integrate Google native WebRTC in iOS apps. 
It is a layer handcrafted over WebRTC native trunk code to obtain audio/video conferencing, text-chat, file sharing and other cool stuff.

ProRTC iOS sample helps you to better understand the features of ProRTC and demonstrates basic integration steps for providing support for the following features in your iPhone/iPad apps:

 - 1x1 video call.
 - Text-chat.

# Screenshots
<p align="left" >
<a href="https://github.com/ProRTC/prortc_ios_samples/blob/master/Screens/Screen%20Shot%202017-01-14%20at%202.15.55%20PM.png">
  <img src="Screens/Screen Shot 2017-01-14 at 2.15.55 PM.png" width="320" height="568" alt="Screenshot1" title="Screenshot1">
</a>
<a href="https://github.com/ProRTC/prortc_ios_samples/blob/master/Screens/Screen%20Shot%202017-01-14%20at%202.18.19%20PM.png">
  <img src="Screens/Screen Shot 2017-01-14 at 2.18.19 PM.png" width="320" height="568" alt="Screenshot2" title="Screenshot2">
</a>
</p>

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
pod 'ProRTC', '1.0.0-beta2'
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

## Contributing
If you want to contribute in WebRTC era, share your ideas, changes and modifications to provide more benefits to developers.

## Known Issues
None at this time.

## Author
[Codiant Software Technology Pvt Ltd](http://www.codiant.com) develops and operates ProRTC.
<br><br>
ProRTC project authors, support@prortc.com

## ProRTC Release-notes
### See [Release-note.markdown](https://github.com/ProRTC/ProRTC/blob/master/Release-note.markdown)

## License
You're free to copy and modify the source code of ProRTC sample project for your own projects. See LICENSE for details.
<br><br>
ProRTC services are available under the Commercial license. See the [Terms](http://prortc.com/terms-conditions.php) for more info.
<br><br>
The ProRTC framework utilizes the following copyrighted projects, the use of which is hereby acknowledged.
* [WebRTC](https://chromium.googlesource.com/external/webrtc/+/master/webrtc/LICENSE)

# If you have any feedback, doubts or feature request, feel free to email us at support@prortc.com
