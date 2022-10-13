//
//  CJGAVAudioPitchEngine.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/16.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "CJGAVAudioInfo.h"
#import "CJGAVAudioPitchEngineInterface.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 声音处理类型
 * @since v3.0
 */
typedef NS_ENUM(NSUInteger, CJGAVSoundPitchType) {
    // 正常
    CJGAVSoundPitchNormal,
    // 怪兽
    CJGAVSoundPitchMonster,
    // 大叔
    CJGAVSoundPitchUncle,
    // 女生
    CJGAVSoundPitchGirl,
    // 萝莉
    CJGAVSoundPitchLolita
};

/**
 录制速度模式
 */
typedef NS_ENUM(NSInteger,CJGAVSoundSpeedMode)
{
    /** 标准模式 速度大小1.0 */
    CJGAVSoundSpeedMode_Normal,
    
    /** 快速模式 速度大小1.5 */
    CJGAVSoundSpeedMode_Fast1,
    
    /** 极快模式 速度大小2.0 */
    CJGAVSoundSpeedMode_Fast2,
    
    /** 慢速模式 速度大小0.7 */
    CJGAVSoundSpeedMode_Slow1,
    
    /** 极慢模式  速度大小0.5 */
    CJGAVSoundSpeedMode_Slow2
};

@protocol CJGAVAudioPitchEngineDelegate;


/**
 音频音调（变声、变速）处理核心工具类
 */
@interface CJGAVAudioPitchEngine : NSObject<CJGAVAudioPitchEngineInterface>

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 * pitchType 与 pitch不能同时设置；因为pitchType就是设置固定值pitch得到的
 */
@property (nonatomic) CJGAVSoundPitchType pitchType;

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 * pitchType 与 pitch不能同时设置；因为pitchType就是设置固定值pitch得到的
 */
@property (nonatomic) float pitch;

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speedMode 与 speed不能同时设置；因为CJGAVSoundSpeedMode就是设置固定值speed得到的
 */
@property (nonatomic) CJGAVSoundSpeedMode speedMode;

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speed 0 > speed
 */
@property (nonatomic) float speed;

/**
 * CJGAVAudioPitchEngineDelegate
 */
@property (nonatomic, weak) id<CJGAVAudioPitchEngineDelegate> delegate;

/**
 * CJGAVAudioPitchEngine初始化
 * @param inputInfo 音频输入样式
 * @return CJGAVAudioPitchEngine
 */
- (instancetype)initWithInputAudioInfo:(CJGAVAudioTrackInfo *)inputInfo;

/**
 * 获取变调系数 [速度设置将失效]
 * @param pitchType 设定的变调类型
 */
- (float)getPitch:(CJGAVSoundPitchType)pitchType;

/**
 * 获取变声系数 [变调设置将失效]
 * @param speedMode 设定的变声类型
 */
- (float)getSpeed:(CJGAVSoundSpeedMode)speedMode;

@end

#pragma mark - CJGAVAudioPitchEngineDelegate

@protocol CJGAVAudioPitchEngineDelegate

/**
 * 输出音频数据
 * @param output CMSampleBufferRef
 * @param autoRelease 是否释放output
 */
- (void)pitchEngine:(CJGAVAudioPitchEngine *)pitchEngine syncAudioPitchOutputBuffer:(CMSampleBufferRef)output autoRelease:(BOOL *)autoRelease;

@end

NS_ASSUME_NONNULL_END
