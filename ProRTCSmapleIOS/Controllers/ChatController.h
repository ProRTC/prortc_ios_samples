//
//  ChatController.h
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "SLKTextViewController.h"

@interface ChatController : SLKTextViewController

@property (strong, nonatomic) NSString *opponentIdStr;
@property (strong, nonatomic) NSMutableArray *messages;

@end
