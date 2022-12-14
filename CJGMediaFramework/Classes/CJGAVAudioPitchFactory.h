//
//  CJGAVAudioPitchFactory.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/16.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CJGAVAudioPitchFactoryInterface.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 音频变调器工厂
 * .mm除了可以包含Objective-C和C代码以外还可以包含C++代码。仅在Objective-C代码中确实需要使用C++类或者特性的时候才用这种扩展名
 */
@interface CJGAVAudioPitchFactory : NSObject<CJGAVAudioPitchFactoryInterface>
/**
 * 音频变调同步协议
 */
@property (nonatomic, weak) id<CJGAVAudioPitchFactorySyncInterface> mediaSync;

/**
 * 切换采样格式
 */
@property (nonatomic, retain) CJGAVAudioTrackInfo *inputInfo;

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 */
@property (nonatomic) float pitch;

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speed 0 > speed
 */
@property (nonatomic) float speed;

/**
 * 是否需要变调
 */
@property (nonatomic, readonly) BOOL needPitch;

/**
 * 创建音频变调器
 * @param info 输入音频轨道信息
 */
+ (id<CJGAVAudioPitchFactoryInterface>)buildWithAudioTrackInfo:(CJGAVAudioTrackInfo *)info;

/**
 * 音频变调
 * @param info 输入音频信息
 */
- (id<CJGAVAudioPitchFactoryInterface>)initWithAudioTrackInfo:(CJGAVAudioTrackInfo *)info;

@end

NS_ASSUME_NONNULL_END
