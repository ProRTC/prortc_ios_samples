//
//  Utils.m
//  ProRTCSmapleIOS
//
//  Created by Utkarsh Singh on 6/22/16.
//  Copyright © 2016 Codiant Software Technologies Pvt Ltd. All rights reserved.
//

#import "Utils.h"

@implementation Utils

+ (void)showAlertMessage:(NSString *)message title:(NSString *)title overViewController:(UIViewController *)viewController
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        [alertController dismissViewControllerAnimated:YES completion:nil];
    }];
    
    [alertController addAction:cancel];
    [viewController presentViewController:alertController animated:YES completion:nil];
}

@end
