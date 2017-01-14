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
#import <ProRTC/ProRTC.h>

@interface VideoCallController () <PWMediaSessionDelegate>
{
    // attribute to determine user is on video calling view or chat view.
    // handle incoming messages accordingly.
    BOOL isOnConferenceVC;
    
    // for unread messages count, to update badge count value.
    NSUInteger unreadCount;
}

// remoteVideoView: An object of PWEAGLVideoView to show remote video.
@property (weak, nonatomic) IBOutlet PWEAGLVideoView *remoteVideoView;

// localVideoView: An object of PWLocalCameraPreview to show local camera video.
@property (weak, nonatomic) IBOutlet PWLocalCameraPreview *localVideoView;

// cameraDisableView: Placeholder view to show when user stops publishing video.
@property (weak, nonatomic) IBOutlet UIView *cameraDisableView;

@property (weak, nonatomic) IBOutlet UIButton *btnAudio;
@property (weak, nonatomic) IBOutlet UIButton *btnVideo;
@property (weak, nonatomic) IBOutlet UIButton *btnHangup;
@property (weak, nonatomic) IBOutlet UIButton *btnSwitchCamera;

// create an object of ProRTC media session, using this object we'll be doing all WebRTC operations.
@property (strong, nonatomic) PWMediaSession *mediaSession;

// Objects to hold local and remote audio/video data.
@property (strong, nonatomic) PWLocalMedia *localMedia;
@property (strong, nonatomic) PWLocalVideoTrack *localVideoTrack;
@property (strong, nonatomic) PWLocalAudioTrack *localAudioTrack;
@property (strong, nonatomic) PWVideoTrack *remoteVideoTrack;

// toggle button parameter.
@property (assign, nonatomic) BOOL isAudioMute;
@property (assign, nonatomic) BOOL isVideoMute;
@property (assign, nonatomic) BOOL isRearFacingCamera;
@property (assign, nonatomic) BOOL isOptionsEnabled;

// var to store remote user id.
@property (strong, nonatomic) PWParticipant *remoteParticipant;

// custom bar button item with badge count (unread messages count).
@property (strong, nonatomic) BBBadgeBarButtonItem *chatButton;

@property (strong, nonatomic) UIActivityIndicatorView *spinner;
@property (strong, nonatomic) UILabel *lblTitle;

@property (strong, nonatomic) NSMutableArray *arrMessages;


@end

@implementation VideoCallController

#pragma mark - Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    NSLog(@"ProRTC version = %@", [PWMediaSession version]);
    
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
    [self prepareUserMeida];
    
    self.mediaSession = [PWMediaSession sharedSession];
    NSString *name = [UIDevice currentDevice].name;
    
    PWConnectOptionsBuilder *connectOptionBuilder = [PWConnectOptionsBuilder new];
    connectOptionBuilder.name = self.roomName;
    connectOptionBuilder.participantName = name;
    connectOptionBuilder.localMedia = self.localMedia;
    
    PWConnectOptions *connectOptions = [[PWConnectOptions alloc] initWithBuilder:connectOptionBuilder];
    [self.mediaSession connectWithOptions:connectOptions delegate:self];
    
    // Stop device to going into sleep mode during video conferencing.
    [self.mediaSession setIdleTimerDisabled:YES];
    
    // add notification observers to perform chat operations. (Send by ChatController.)
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newMessageSent:) name:@"newMessageSent" object:nil];
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

- (void)dismissing
{
    isOnConferenceVC = YES;
}

#pragma mark - Private

- (void)prepareUserMeida
{
    if (!self.localMedia) {
        self.localMedia = [[PWLocalMedia alloc] init];
    }
    
    if (!self.localAudioTrack) {
        self.localAudioTrack = [self.localMedia addAudioTrack:YES];
    }
    
    if (!self.localVideoTrack) {
        self.localVideoTrack = [self.localMedia addVideoTrack:YES];
    }
    
    [self.localVideoView bindWithLocalVideoTrack:self.localVideoTrack];
}

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
    NSLog(@"connected to room %@ as %@", room.name, self.mediaSession.localParticipant.name);
}

- (void)mediaSession:(PWMediaSession *)session didDisconnectFromRoom:(PWRoom *)room
{
    NSLog(@"disconnected from room %@", room.name);
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
    NSLog(@"fail with error description %@\nfailure reason %@ error code %ld", error.localizedDescription, error.localizedFailureReason, (long)error.code);
    
    if (error) {
        
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:error.localizedDescription message:error.localizedFailureReason preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction *disconnect = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
            
            // on any kind of error, performing end call operation here.
            [self btnHangup_Action:self.btnHangup];
        }];
        
        [alertController addAction:disconnect];
        [self presentViewController:alertController animated:YES completion:nil];
        
        // For performing different operations on different error.
        // @See: PWError.h
    }
}

- (void)mediaSession:(PWMediaSession *)session didJoinNewParticipant:(PWParticipant *)participant
{
    NSLog(@"new participant joined as %@", participant.sid);
}

- (void)mediaSession:(PWMediaSession *)session addedVideoTrack:(PWVideoTrack *)videoTrack ofParticipant:(PWParticipant *)participant
{
    NSLog(@"added video of participant %@", participant.sid);
    self.remoteVideoTrack = videoTrack;
    self.remoteParticipant = participant;
    
    // start rendering of remote video.
    [self.remoteVideoView bindTrack:self.remoteVideoTrack];
    
    if (!self.isOptionsEnabled) {
        [self enableOptions];
    }
}

- (void)mediaSession:(PWMediaSession *)session didReceiveTextMessage:(NSString *)message ofParticipant:(PWParticipant *)participant
{
    Message *objMessage = [Message new];
    objMessage.username = participant.name;
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

- (void)mediaSession:(PWMediaSession *)session didDisconnectParticipant:(PWParticipant *)participant
{
    NSLog(@"participant disconnected %@", participant.sid);
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
    
    chatController.opponentIdStr = self.remoteParticipant.sid;
    chatController.messages = self.arrMessages;
    [self presentViewController:navController animated:YES completion:nil];
}

- (IBAction)btnAudio_Action:(id)sender {
    
    if (self.isAudioMute) {
        self.localAudioTrack.enabled = YES;
        [self.btnAudio setImage:[UIImage imageNamed:@"audioOn"] forState:UIControlStateNormal];
        self.isAudioMute = NO;
    }
    else {
        self.localAudioTrack.enabled = NO;
        [self.btnAudio setImage:[UIImage imageNamed:@"audioOff"] forState:UIControlStateNormal];
        self.isAudioMute = YES;
    }
    
    NSLog(@"Audio disabled: %i", self.isAudioMute);
}

- (IBAction)btnVideo_Action:(id)sender {
    
    if (self.isVideoMute) {
        self.localVideoTrack.enabled = YES;
        [self.btnVideo setImage:[UIImage imageNamed:@"videoOn"] forState:UIControlStateNormal];
        self.isVideoMute = NO;
    }
    else {
        self.localVideoTrack.enabled = NO;
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
    
    if (!self.localMedia.canUseBackCamera) {
        NSLog(@"Rear-facing camera source not available.");
        return;
    }
    
    self.isRearFacingCamera = !self.isRearFacingCamera;
    self.localMedia.useBackCamera = self.isRearFacingCamera;
}

- (IBAction)btnHangup_Action:(id)sender {
    
    // Enable device idle timer that you disabled when your call started, you don't want user's device to be active always.
    [self.mediaSession setIdleTimerDisabled:NO];
    
    // stop rendering.
    if (self.remoteVideoTrack) {
        [self.remoteVideoView unBindTrack:self.remoteVideoTrack];
        self.remoteVideoTrack = nil;
    }

    self.localVideoTrack = nil;
    self.localAudioTrack = nil;
    
    // end call.
    [self.mediaSession disconnect];
    self.localMedia = nil;
    self.remoteParticipant = nil;
    self.mediaSession = nil;
    
    [self.navigationController popViewControllerAnimated:YES];
}

@end
