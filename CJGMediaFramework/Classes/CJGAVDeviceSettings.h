//
//  AudioVideoDeviceSettings.h
//  AudioVideoSDK
//
//  Created by Jinguo Chen on 2022/6/6.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVSettings.h"


NS_ASSUME_NONNULL_BEGIN
/**
 *  系统相册授权错误
 */
typedef NS_ENUM(NSInteger, CJGAVAssetsAuthorizationError){
    /**
     *  未定义
     */
    CJGAVAssetsAuthorizationErrorNotDetermined = 0,
    /**
     *  限制访问
     */
    CJGAVAssetsAuthorizationErrorRestricted,
    /**
     *  拒绝访问
     */
    CJGAVAssetsAuthorizationErrorDenied
};

/**
 *  系统相册授权回调
 *
 *  @param error 是否返回错误信息
 */
typedef void (^CJGAVSDKTSAssetsManagerAuthorBlock)(NSError *error);

/**
 *  系统相册授权回调
 *
 *  @param error 是否返回错误信息
 */
typedef void (^CJGAVAssetsLibraryAuthorBlock)(NSError *error);

@interface CJGAVDeviceSettings : CJGAVSettings

#pragma mark - Camera
/**
 *  测试系统摄像头授权状态
 *
 *  @return    返回是否授权
 */
+ (BOOL)hasVideoAuthor;

/**
 *  相机设备总数
 *
 *  @return 相机设备总数
 */
+ (int)getCameraCounts;

/**
 *  获取相机设备（前置或后置） 后置优先
 *
 *  @return 相机设备
 */
+ (AVCaptureDevice *)getBackOrFrontCamera;


#pragma mark - Photo
/**
 *  是否用户已授权访问系统相册
 *
 *  @return 是否用户已授权访问系统相册
 */
+ (BOOL)hasAuthor;
/**
 *  是否未决定授权
 *
 *  @return 是否未决定授权
 */
+ (BOOL)notDetermined;

/**
 *  低版本小于8.0测试系统相册授权状态
 *
 *  @param authorBlock 系统相册授权回调
 */
+ (void)lowVersionTestLibraryAuthor:(CJGAVSDKTSAssetsManagerAuthorBlock)authorBlock;

/**
 *  测试系统相册授权状态
 *
 *  @param authorBlock 系统相册授权回调
 */
+ (void)testLibraryAuthor:(CJGAVSDKTSAssetsManagerAuthorBlock)authorBlock;

#pragma mark - Microphone
/**
 *  是否用户已授权访问系统麦克风
 *
 *  @return 是否用户已授权访问系统麦克风
 */
+ (BOOL)haseMicrophoneAuthor;
@end

NS_ASSUME_NONNULL_END
