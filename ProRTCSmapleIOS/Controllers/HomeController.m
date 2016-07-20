//
//  HomeController.m
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "HomeController.h"
#import "VideoCallController.h"

@interface HomeController ()

@property (weak, nonatomic) IBOutlet UITextField *txfRoom;

@property (weak, nonatomic) IBOutlet UIButton *btnJoin;

@end

@implementation HomeController

#pragma mark - Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - UITextField delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    
    [textField resignFirstResponder];
    
    return YES;
}

#pragma mark - IBActions

- (IBAction)textDidChange:(UITextField *)sender {
    self.btnJoin.enabled = [sender.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]].length;
}

- (IBAction)btnJoin_Action:(id)sender {
    
    if (!appDelegate().isNetworkReachable) {
        [Utils showAlertMessage:@"No working Internet connection is found.\n\nIf Wi-Fi enabled, try disabling Wi-Fi or try another Wi-Fi hotspot." title:@"No Internet! 😟" overViewController:self];
        return;
    }
    
    [self.txfRoom resignFirstResponder];
    [self performSegueWithIdentifier:@"pushToVideoCall" sender:self];
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    
    if ([segue.identifier isEqualToString:@"pushToVideoCall"]) {
        
        VideoCallController *videoCallController = [segue destinationViewController];
        videoCallController.roomName = [self.txfRoom.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
    }
}

@end
