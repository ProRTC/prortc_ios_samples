//
//  Message.h
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Message : NSObject

@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *text;
@property (nonatomic, strong) NSString *selectedUser;

@property (nonatomic, assign) BOOL isOutgoing;

@end
