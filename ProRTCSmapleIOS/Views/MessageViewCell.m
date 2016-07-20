//
//  MessageViewCell.m
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "MessageViewCell.h"
#import "SLKTextView+SLKAdditions.h"
#import "SLKUIConstants.h"

@implementation MessageViewCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    
    if (self) {
        self.selectionStyle  = UITableViewCellSelectionStyleNone;
        self.backgroundColor = [UIColor whiteColor];
        
        [self configureSubviews];
    }
    
    return self;
}

- (void)configureSubviews
{
    [self.contentView addSubview:self.thumbnailView];
    [self.contentView addSubview:self.titleLabel];
    [self.contentView addSubview:self.bodyLabel];
    
    NSDictionary *views = @{@"thumbnailView": self.thumbnailView,
                            @"titleLabel"   : self.titleLabel,
                            @"bodyLabel"    : self.bodyLabel,
                            };
    
    NSDictionary *metrics = @{@"tumbSize": @(kMessageTableViewCellAvatarHeight),
                              @"padding" : @15,
                              @"right"   : @10,
                              @"left"    : @12
                              };
    
    [self.contentView addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-left-[thumbnailView(tumbSize)]-right-[titleLabel(>=0)]-right-|" options:0 metrics:metrics views:views]];
    [self.contentView addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-left-[thumbnailView(tumbSize)]-right-[bodyLabel(>=0)]-right-|" options:0 metrics:metrics views:views]];
    [self.contentView addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-right-[thumbnailView(tumbSize)]-(>=0)-|" options:0 metrics:metrics views:views]];
    
    if ([self.reuseIdentifier isEqualToString:MessengerCellIdentifier]) {
        [self.contentView addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-right-[titleLabel(20)]-left-[bodyLabel(>=0@999)]-left-|" options:0 metrics:metrics views:views]];
    }
    else {
        [self.contentView addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|[titleLabel]|" options:0 metrics:metrics views:views]];
    }
}

- (void)prepareForReuse
{
    [super prepareForReuse];
    
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    CGFloat pointSize   = [MessageViewCell defaultFontSize];
    
    self.titleLabel.font = [UIFont boldSystemFontOfSize:pointSize];
    self.bodyLabel.font  = [UIFont systemFontOfSize:pointSize];
    
    self.titleLabel.text = @"";
    self.bodyLabel.text  = @"";
}

#pragma mark - Getters

- (UILabel *)titleLabel
{
    if (!_titleLabel) {
        _titleLabel = [UILabel new];
        _titleLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _titleLabel.backgroundColor = [UIColor clearColor];
        _titleLabel.userInteractionEnabled = NO;
        _titleLabel.numberOfLines = 0;
        _titleLabel.textColor = [UIColor grayColor];
        _titleLabel.font = [UIFont boldSystemFontOfSize:[MessageViewCell defaultFontSize]];
    }
    return _titleLabel;
}

- (UILabel *)bodyLabel
{
    if (!_bodyLabel) {
        _bodyLabel = [UILabel new];
        _bodyLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _bodyLabel.backgroundColor = [UIColor clearColor];
        _bodyLabel.userInteractionEnabled = NO;
        _bodyLabel.numberOfLines = 0;
        _bodyLabel.textColor = [UIColor darkGrayColor];
        _bodyLabel.font = [UIFont systemFontOfSize:[MessageViewCell defaultFontSize]];
    }
    return _bodyLabel;
}

- (UIImageView *)thumbnailView
{
    if (!_thumbnailView) {
        _thumbnailView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 30, 30)];
        _thumbnailView.translatesAutoresizingMaskIntoConstraints = NO;
        _thumbnailView.userInteractionEnabled = NO;
        _thumbnailView.backgroundColor = [UIColor colorWithWhite:0.9 alpha:1.0];
        
        _thumbnailView.layer.cornerRadius = kMessageTableViewCellAvatarHeight/2.0;
        _thumbnailView.layer.masksToBounds = YES;
    }
    return _thumbnailView;
}

+ (CGFloat)defaultFontSize
{
    CGFloat pointSize = 16.0;
    
    __unused NSString *contentSizeCategory = [[UIApplication sharedApplication] preferredContentSizeCategory];
    //pointSize += [SLKTextView pointSizeDifferenceForCategory:contentSizeCategory];
    
    return pointSize;
}

@end
