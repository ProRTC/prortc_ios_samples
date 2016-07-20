//
//  VideoCallController.m
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "VideoCallController.h"

#import "ChatController.h"

#import "BBBadgeBarButtonItem.h"

#import "Message.h"

// ProRTC
#import "ProRTC.h"

@interface VideoCallController () <PWMediaSessionDelegate>
{
    // attribute to determine user is on video calling view or chat view.
    // handle incoming messages accordingly.
    BOOL isOnConferenceVC;
    
    // for unread messages count, to update badge count value.
    NSUInteger unreadCount;
}

// remoteVideoView: An object of RTCEAGLVideoView to show remote video.
@property (weak, nonatomic) IBOutlet RTCEAGLVideoView *remoteVideoView;

// localVideoView: An object of RTCEAGLVideoView to show local camera video.
@property (weak, nonatomic) IBOutlet RTCEAGLVideoView *localVideoView;

// cameraDisableView: Placeholder view to show when user stops publishing video.
@property (weak, nonatomic) IBOutlet UIView *cameraDisableView;


@property (weak, nonatomic) IBOutlet UIButton *btnAudio;
@property (weak, nonatomic) IBOutlet UIButton *btnVideo;
@property (weak, nonatomic) IBOutlet UIButton *btnHangup;
@property (weak, nonatomic) IBOutlet UIButton *btnSwitchCamera;


// create an object of ProRTC media session, using this object we'll be doing all WebRTC operations.
@property (strong, nonatomic) PWMediaSession *mediaSession;


// RTCVideoTrack objects to hold local and remote videos data.
@property (strong, nonatomic) RTCVideoTrack *localVideoTrack;
@property (strong, nonatomic) RTCVideoTrack *remoteVideoTrack;


// you can also create PWMediaConfiguration object, If you want to set custom media properties.
//
// e.g. PWMediaConfiguration *config = [PSMediaConfiguration defaultConfiguration];
//      config.maxAudioBitrate = PSMediaSessionMaximumAudioRateMultiparty
//      config.maxVideoBitrate = ...
//      config.cameraPosition = ...
//      config.preferredVideoCodec = ... etc..


// toggle button parameter.
@property (assign, nonatomic) BOOL isAudioMute;
@property (assign, nonatomic) BOOL isVideoMute;
@property (assign, nonatomic) BOOL isOptionsEnabled;

// var to store remote user id.
@property (copy, nonatomic) NSString *remoteUserId;


// custom bar button item with badge count (unread messages count).
@property (strong, nonatomic) BBBadgeBarButtonItem *chatButton;

//...
@property (strong, nonatomic) UIActivityIndicatorView *spinner;
@property (strong, nonatomic) UILabel *lblTitle;

@property (strong, nonatomic) NSMutableArray *arrMessages;


@end

@implementation VideoCallController

#pragma mark - Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navigationItem.hidesBackButton = YES;
    self.arrMessages = [NSMutableArray new];
    isOnConferenceVC = YES;
    
    // drop a little shadow to highlight our local video view.
    self.localVideoView.layer.masksToBounds = NO;
    self.localVideoView.layer.shadowOffset  = CGSizeMake(-5, 5);
    self.localVideoView.layer.shadowRadius  = 5;
    self.localVideoView.layer.shadowOpacity = 0.5;
    self.localVideoView.layer.shadowColor   = [UIColor blackColor].CGColor;
    
    
    // Initialize session.
    self.mediaSession = [PWMediaSession sharedInstance];
    
    
    
    // ProRTC also includes support for datachannels.
    // With the help of datachannels you can transfer files or even you can also send text messages.
    //
    // because this sample also includes 1x1 video call with text messaging, it's using datachannels for text messaging here.
    //
    // if datachannels are not enabled, file sharing will not work but text messaging will.
    // by default session checks, If datachannels are enabled private messages will be sent through channels not server.
    // if disabled, messages will be sent through server.
    //
    // group chat does not support datachannels for now.
    //
    // @warning: This line of code must be written before initiating call.
    //
    // do not forget to disbale it, If not using, It'll save processing time.
    //
    PWMediaSessionEnableDataChannels(YES);
    
    
    
    // Start video call.
    // @param: room name or any unique identifier.
    // @param: participant id --
    // @param: participant name --
    // @param: delegate <PWMediaSessionDelegate>
    //
    // It's just a sample and we're not maintaining user data so passing [NSUUID UUID] in participant id and name.
    // You can pass your own values If you want.
    //
    
    NSString *GUID = [NSUUID UUID].UUIDString;
    NSString *name = [UIDevice currentDevice].name;
    
    [self.mediaSession startVideoCall:self.roomName participant:GUID displayName:name delegate:self];
    
    
    // For custom media properties.
    // You can use this method:
    //  **  [self.mediaSession startVideoCall:<#(NSString *)#> participant:<#(NSString *)#> displayName:<#(NSString *)#> delegate:<#(id<PWMediaSessionDelegate>)#> configuration:<#(PWMediaConfiguration *)#>];**
    //
    
    
    // For only audio calling.
    // You can use this method:
    //  **  [self.mediaSession startAudioCall:<#(NSString *)#> participant:<#(NSString *)#> displayName:<#(NSString *)#> delegate:<#(id<PWMediaSessionDelegate>)#>];**
    //
    
    
    // add notification observers to perform chat operations. (Send by ChatController.)
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newMessageSent:) name:@"newMessageSent" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newPrivateMessageSent:) name:@"newPrivateMessageSent" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dismissing) name:@"dismissing" object:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - NSNotificationCenter

- (void)newMessageSent:(NSNotification *)notif
{
    if (notif.object) {
        
        Message *message = notif.object;
        [self.mediaSession sendMessage:message.text];
    }
}

- (void)newPrivateMessageSent:(NSNotification *)notif
{
    if (notif.object) {
        
        Message *message = notif.object;
        [self.mediaSession sendMessage:message.text toPeer:message.selectedUser];
    }
}

- (void)dismissing
{
    isOnConferenceVC = YES;
}

#pragma mark - Private

- (void)enableOptions {
    
    [UIView transitionWithView:self.btnAudio
                      duration:1.5
                       options:UIViewAnimationOptionTransitionFlipFromLeft
                    animations:^{
                        self.btnAudio.hidden = NO;
                    } completion:nil];
    
    [UIView transitionWithView:self.btnVideo
                      duration:1.5
                       options:UIViewAnimationOptionTransitionFlipFromLeft
                    animations:^{
                        self.btnVideo.hidden = NO;
                    } completion:nil];
    
    [UIView transitionWithView:self.btnSwitchCamera
                      duration:1.5
                       options:UIViewAnimationOptionTransitionFlipFromLeft
                    animations:^{
                        self.btnSwitchCamera.hidden = NO;
                    } completion:nil];

    self.isOptionsEnabled = YES;
    [self setupNavigationBar];
}


// Custom navigation bar title view.
// Showing connectivity status with activity indicator.
- (void)showActivityIndicator
{
    self.spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    self.spinner.frame = CGRectMake(0, 0, 22, 22);
    self.spinner.color = [UIColor blackColor];
    [self.spinner startAnimating];
    
    self.lblTitle = [UILabel new];
    self.lblTitle.text = @"Connecting...";
    self.lblTitle.font = [UIFont boldSystemFontOfSize:18.0f];
    
    CGSize fittingSize = [self.lblTitle sizeThatFits:CGSizeMake(200.0f, self.spinner.frame.size.height)];
    self.lblTitle.frame = CGRectMake(self.spinner.frame.origin.x + self.spinner.frame.size.width + 8, self.spinner.frame.origin.y, fittingSize.width, fittingSize.height);
    
    UIView *titleView = [[UIView alloc] initWithFrame:CGRectMake(-(self.spinner.frame.size.width + 8 + self.lblTitle.frame.size.width)/2, -(self.spinner.frame.size.height)/2, self.spinner.frame.size.width + 8 + self.lblTitle.frame.size.width, self.spinner.frame.size.height)];
    
    [titleView addSubview:self.spinner];
    [titleView addSubview:self.lblTitle];
    
    self.navigationItem.titleView = titleView;
}


/**
 * Setup chat icon in navigation bar.
 */
- (void)setupNavigationBar {
    
    UIImage *cartImage = [UIImage imageNamed:@"chatBubble"];
    UIButton *customButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, cartImage.size.width, cartImage.size.height)];
    [customButton setImage:cartImage forState:UIControlStateNormal];
    [customButton addTarget:self action:@selector(didPressedChat) forControlEvents:UIControlEventTouchUpInside];
    
    // Create and add our custom BBBadgeBarButtonItem.
    self.chatButton                         = [[BBBadgeBarButtonItem alloc] initWithCustomUIButton:customButton];
    self.chatButton.shouldAnimateBadge      = YES;
    self.chatButton.shouldHideBadgeAtZero   = YES;
    self.chatButton.badgePadding            = 04.0f;
    self.chatButton.badgeOriginX            = 13.0f;
    self.chatButton.badgeTextColor          = [UIColor whiteColor];
    self.chatButton.badgeBGColor            = [UIColor redColor];
    
    self.navigationItem.rightBarButtonItem = self.chatButton;
}


#pragma mark - PSMediaSession delegate

/**
 *  For more details on PWMediaSession delegates. See ProRTC library documentation.
 */

- (void)mediaSession:(PWMediaSession *)session didConnectToRoom:(PWRoom *)room
{
    NSLog(@"Connected to room: %@", room.meetingId);
}

- (void)mediaSession:(PWMediaSession *)session didDisconnectToRoom:(PWRoom *)room
{
    NSLog(@"Disconnected to room: %@", room.meetingId);
}

- (void)mediaSession:(PWMediaSession *)session didChangeState:(PWConnectionState)state
{
    switch (state) {
            
        case PWConnectionStateConnecting:
            
            [self showActivityIndicator];
            
            break;
            
        case PWConnectionStateConnected:
            
            [self.spinner stopAnimating];
            self.lblTitle.text = self.roomName;
            
            break;
            
        case PWConnectionStateDisconnected:
            
            [self.spinner stopAnimating];
            self.lblTitle.text = @"Disconnected";
            
            break;
            
        default:
            break;
    }
}

- (void)mediaSession:(PWMediaSession *)session didFailWithError:(NSError *)error
{
    NSLog(@"Fail with error description: %@ \n Failure reason: %@ Error code: %ld", error.localizedDescription, error.localizedFailureReason, (long)error.code);
    
    if (error) {
        
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:error.localizedDescription message:error.localizedFailureReason preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction *disconnect = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
            
            // on any kind of error, performing end call operation here.
            [self btnHangup_Action:self.btnHangup];
        }];
        
        [alertController addAction:disconnect];
        [self presentViewController:alertController animated:YES completion:nil];
        
        
        // For performing different operations on different error.
        // @See: kWebSocketErrorCode (defined in PWTypes.h)
    }
}

- (void)mediaSession:(PWMediaSession *)session didAddLocalStream:(RTCMediaStream *)localStream
{
    // No need of rendering in case of audio conferencing.
    if (localStream.isVideoTrackAvailable) {
        
        // save video track of media stream.
        self.localVideoTrack = localStream.videoTracks[0];
        
        // start rendering of local camera video.
        [self.localVideoTrack bindRendererView:self.localVideoView];
    }
    
    // Stop device to going into sleep mode during video conferencing.
    [self.mediaSession setIdleTimerDisabled:YES];
}

- (void)mediaSession:(PWMediaSession *)session didAddRemoteStream:(RTCMediaStream *)remoteStream ofPeer:(PWRemotePeer *)remotePeer
{
    // No need of rendering in case of audio conferencing.
    if (remoteStream.isVideoTrackAvailable) {
        
        // save video track of media stream.
        self.remoteVideoTrack = remoteStream.videoTracks[0];
        
        // start rendering of remote camera video.
        [self.remoteVideoTrack bindRendererView:self.remoteVideoView];
        
        // save remote user id, will be useful for further operation e.g. sending messages.
        self.remoteUserId = remotePeer.peerId;
    }
    
    if (!self.isOptionsEnabled) {
        [self enableOptions];
    }
}

- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofPeer:(PWRemotePeer *)remotePeer
{
    Message *objMessage = [Message new];
    objMessage.username = remotePeer.displayName;
    objMessage.text     = message;
    
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
    
    // If user on video call view, show the unread message badge count.
    // ELSE
    // Post notification to chat controller to update message on chat screen.
    if (isOnConferenceVC) {
        [self.arrMessages insertObject:objMessage atIndex:0];
        unreadCount++;
        [self.chatButton setBadgeValue:[NSString stringWithFormat:@"%lu", (unsigned long)unreadCount]];
    }
    else {
        [[NSNotificationCenter defaultCenter] postNotificationName:@"newMessageReceived" object:objMessage];
    }
}

- (void)mediaSession:(PWMediaSession *)session didDisconnectPeer:(PWRemotePeer *)remotePeer
{
    NSLog(@"Peer left room: %@", remotePeer.peerId);
    
    // If 1x1 then no need to stay :P, end call here.
    [self btnHangup_Action:self.btnHangup];
}


#pragma mark - IBActions

- (void)didPressedChat
{
    isOnConferenceVC = NO;
    unreadCount = 0;
    [self.chatButton setBadgeValue:[NSString stringWithFormat:@"%lu", (unsigned long)unreadCount]];
    
    ChatController *chatController = [self.storyboard instantiateViewControllerWithIdentifier:NSStringFromClass([ChatController class])];
    
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:chatController];
    
    chatController.opponentIdStr = self.remoteUserId;
    chatController.messages = self.arrMessages;
    [self presentViewController:navController animated:YES completion:nil];
}

- (IBAction)btnAudio_Action:(id)sender {
    
    if (self.isAudioMute) {
        [self.mediaSession startMic];
        [self.btnAudio setImage:[UIImage imageNamed:@"audioOn"] forState:UIControlStateNormal];
        self.isAudioMute = NO;
    }
    else {
        [self.mediaSession stopMic];
        [self.btnAudio setImage:[UIImage imageNamed:@"audioOff"] forState:UIControlStateNormal];
        self.isAudioMute = YES;
    }
    
    NSLog(@"Audio disabled: %i", self.isAudioMute);
}

- (IBAction)btnVideo_Action:(id)sender {
    
    if (self.isVideoMute) {
        [self.mediaSession startCamera];
        [self.btnVideo setImage:[UIImage imageNamed:@"videoOn"] forState:UIControlStateNormal];
        self.isVideoMute = NO;
    }
    else {
        [self.mediaSession stopCamera];
        [self.btnVideo setImage:[UIImage imageNamed:@"videoOff"] forState:UIControlStateNormal];
        self.isVideoMute = YES;
    }
    
    // show OR hide camera diabled placeholder view.
    self.cameraDisableView.hidden = !self.isVideoMute;
    
    // hide camera switch button if video is mute.
    self.btnSwitchCamera.hidden = self.isVideoMute;
    
    NSLog(@"Video disabled: %i", self.isVideoMute);
}

- (IBAction)btnSwitchCamera_Action:(id)sender
{
    NSLog(@"Switching camera position.");
    
    if (self.mediaSession.cameraPosition == PWCameraPositionFront) {
        [self.mediaSession switchCameraPosition:PWCameraPositionBack];
    }
    else {
        [self.mediaSession switchCameraPosition:PWCameraPositionFront];
    }
}

- (IBAction)btnHangup_Action:(id)sender {
    
    // stop rendering.
    if (self.remoteVideoTrack) [self.remoteVideoTrack unBindRendererView:self.remoteVideoView];
    if (self.localVideoTrack) [self.localVideoTrack unBindRendererView:self.localVideoView];
    
    // remove stored videos data.
    self.localVideoTrack = nil;
    self.remoteVideoTrack = nil;
    
    // remove rendered layer.
    [self.localVideoView renderFrame:nil];
    [self.remoteVideoView renderFrame:nil];
    
    // end call.
    [self.mediaSession endCall];
    
    // Enable device idle timer that you disabled when your call started, you don't want user's device to be active always.
    [self.mediaSession setIdleTimerDisabled:NO];
    
    [self.navigationController popViewControllerAnimated:YES];
}

@end
