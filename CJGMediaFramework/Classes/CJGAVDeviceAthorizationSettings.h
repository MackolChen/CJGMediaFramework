//
//  AudioVideoDeviceuAthorizationSettings.h
//  AudioVideoSDK
//
//  Created by Jinguo Chen on 2022/6/6.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVDeviceSettings.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  设备权限设置类型
 */
typedef NS_ENUM(NSInteger, CJGAVDeviceAthorizationSettingsType)
{
    /**
     *  未知类型
     */
    CJGAVDeviceAthorizationSettingsUnknow,
    /**
     *  设置照片权限
     */
    CJGAVDeviceAthorizationSettingsPhoto,
    /**
     * 设置相机权限
     */
    CJGAVDeviceAthorizationSettingsCamera,
    /**
     * 设置定位权限
     */
    CJGAVDeviceAthorizationSettingsLocation,
    /**
     *  设置照片权限
     */
    CJGAVDeviceAthorizationSettingsMicrophone,
    /**其他权限设置*/
};

/**
 *  设备权限设置
 *
 *  @param type        设备权限设置类型
 *  @param openSetting 是否开启权限设置
 */
typedef void (^CJGAVDeviceAthorizationSettingsBlock)(CJGAVDeviceAthorizationSettingsType type, BOOL openSetting);

@interface CJGAVDeviceAthorizationSettings : CJGAVDeviceSettings


/**
 *  检查设备权限
 *
 *  @param controller UIViewController
 *  @param type       设备权限设置类型
 *  @param completed  设备权限设置
 */
+ (void)checkAllowWithController:(UIViewController *)controller type:(CJGAVDeviceAthorizationSettingsType)type completed:(CJGAVDeviceAthorizationSettingsBlock)completed;

@end

NS_ASSUME_NONNULL_END
