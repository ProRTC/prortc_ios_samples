//
//  MessageViewCell.h
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

static CGFloat kMessageTableViewCellMinimumHeight   = 50.0;
static CGFloat kMessageTableViewCellAvatarHeight    = 30.0;

static NSString *MessengerCellIdentifier        = @"MessengerCell";
static NSString *AutoCompletionCellIdentifier   = @"AutoCompletionCell";

@interface MessageViewCell : UITableViewCell

@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *bodyLabel;
@property (nonatomic, strong) UIImageView *thumbnailView;

@property (nonatomic, strong) NSIndexPath *indexPath;

@property (nonatomic) BOOL usedForMessage;

+ (CGFloat)defaultFontSize;

@end
