//
//  AudioVideoSettings.h
//  AudioVideoSDK
//
//  Created by Jinguo Chen on 2022/6/6.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import <UIKit/UIKit.h>
#import <Photos/Photos.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 应用的相关设置信息核心类
 */
@interface CJGAVSettings : NSObject

/**
 *  获取应用名称
 *
 *  @return 应用名称
 */
+ (NSString *)getAppName;
/**
 *  系统版本号
 *
 *  @return 系统版本号 e.g. @"4.0"
 */
+ (CGFloat)getSystemFloatVersion;

/**
 *  系统版本号
 *
 *  @return 系统版本号 e.g. @"4.0.2"
 */
+ (NSString *)getSystemVersion;
@end

NS_ASSUME_NONNULL_END
