//
//  CJGAVAudioPitchEngineRecorderOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/8/1.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVAudioRecorderOptions.h"
#import "CJGAVAudioPitchEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface CJGAVAudioPitchEngineRecorderOptions : CJGAVAudioRecorderOptions
{
    //目的：在变速与变调混合情况下，应对不同的设置模式，进行唯一设置单一有效结果
    BOOL _isSetPitch;
    BOOL _isSetPitchType;
    BOOL _isSetSpeed;
    BOOL _isSetSpeedMode;
}

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 * pitchType 与 pitch不能同时设置；因为pitchType就是设置固定值pitch得到的
 */
@property (nonatomic, assign) CJGAVSoundPitchType pitchType;

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 * pitchType 与 pitch不能同时设置；因为pitchType就是设置固定值pitch得到的
 */
@property (nonatomic, assign) float pitch;

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speedMode 与 speed不能同时设置；因为CJGAVSoundSpeedMode就是设置固定值speed得到的
 */
@property (nonatomic, assign) CJGAVSoundSpeedMode speedMode;

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speed 0 > speed
 */
@property (nonatomic, assign) float speed;

//目的：在变速与变调混合情况下，应对不同的设置模式，进行唯一设置单一有效结果
@property (nonatomic, readonly) BOOL isSetPitch;
@property (nonatomic, readonly) BOOL isSetPitchType;
@property (nonatomic, readonly) BOOL isSetSpeed;
@property (nonatomic, readonly) BOOL isSetSpeedMode;

@end

NS_ASSUME_NONNULL_END
