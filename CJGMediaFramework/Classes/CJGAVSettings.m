//
//  AudioVideoSettings.m
//  AudioVideoSDK
//
//  Created by Jinguo Chen on 2022/6/6.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVSettings.h"

@implementation CJGAVSettings

/**
 *  获取应用名称
 *
 *  @return 应用名称
 */
+ (NSString *)getAppName;
{
    NSString *appName = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleNameKey];
    
    // 从InfoPlist.strings 读取
    if (!appName) appName = [[NSBundle mainBundle] localizedStringForKey:@"CFBundleDisplayName" value:nil table:@"InfoPlist"];
    
    return appName;
}

/**
 *  系统版本号
 *
 *  @return 系统版本号 e.g. @"4.0"
 */
+ (CGFloat)getSystemFloatVersion;
{
    return [[self getSystemVersion] floatValue];
}

/**
 *  系统版本号
 *
 *  @return 系统版本号 e.g. @"4.0.2"
 */
+ (NSString *)getSystemVersion;
{
    return [[UIDevice currentDevice] systemVersion];
}
@end
