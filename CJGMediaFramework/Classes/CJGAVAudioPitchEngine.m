//
//  CJGAVAudioPitchEngine.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/16.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVAudioPitchEngine.h"
#import "CJGAVAudioPitchFactory.h"

@interface CJGAVAudioPitchEngine()<CJGAVAudioPitchFactorySyncInterface>

@property (nonatomic, strong) id<CJGAVAudioPitchFactoryInterface> audioPitch;

@end

@implementation CJGAVAudioPitchEngine

/**
 * CJGAVAudioPitchEngine初始化
 * @param inputInfo 音频输入样式
 * @return CJGAVAudioPitchEngine
 * @since v3.0
 */
- (instancetype)initWithInputAudioInfo:(CJGAVAudioTrackInfo *)inputInfo;
{
    if (self = [super init]) {
        
        if(!inputInfo) return nil;
        
        _audioPitch = [CJGAVAudioPitchFactory buildWithAudioTrackInfo:inputInfo];
        _audioPitch.mediaSync = self;
    }
    return self;
}

#pragma mark -- setter getter

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 * pitchType 与 pitch不能同时设置；因为pitchType就是设置固定值pitch得到的
 */
- (void)setPitchType:(CJGAVSoundPitchType)pitchType{
    if(_pitchType == pitchType) return;
    
    _pitchType = pitchType;
    _speedMode = CJGAVSoundSpeedMode_Normal;
    _speed = 1;
    float pitch = [self getPitch:pitchType];
    if (_audioPitch) _audioPitch.pitch = pitch;
}

/**
 * 改变音频音调 [速度设置将失效]
 * pitch 0 > pitch [大于1时声音升调，小于1时为降调]
 * pitchType 与 pitch不能同时设置；因为pitchType就是设置固定值pitch得到的
 */
- (void)setPitch:(float)pitch{
    if(_pitch == pitch) return;
    _pitch = pitch;
    _pitchType = CJGAVSoundPitchNormal;
    _speed = 1;
    _speedMode = CJGAVSoundSpeedMode_Normal;
    if (_audioPitch) _audioPitch.pitch = _pitch;
}

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speedMode 与 speed不能同时设置；因为CJGAVSoundSpeedMode就是设置固定值speed得到的
 */
- (void)setSpeedMode:(CJGAVSoundSpeedMode)speedMode{
    if(_speedMode == speedMode) return;
    
    _speedMode = speedMode;
    _pitch = 1.0;
    _pitchType = CJGAVSoundPitchNormal;
    _speed = 1;
    float speed = [self getSpeed:speedMode];
    if (_audioPitch) _audioPitch.speed = speed;
}

/**
 * 改变音频播放速度 [变速不变调, 音调设置将失效]
 * speed 0 > speed
 */
- (void)setSpeed:(float)speed;
{
    if(_speed == speed) return;
    _speed = speed;
    _speedMode = CJGAVSoundSpeedMode_Normal;
    _pitchType = CJGAVSoundPitchNormal;
    _pitch = 1;
    if (_audioPitch) _audioPitch.speed = speed;
}

/**
 * 获取变调系数 [速度设置将失效]
 * @param pitchType 设定的变调类型
 */
- (float)getPitch:(CJGAVSoundPitchType)pitchType;{
    float pitch;
    switch (pitchType) {
        case CJGAVSoundPitchNormal:
            pitch = 1.0;
            break;
        case CJGAVSoundPitchMonster:
            pitch = 0.6;
            break;
        case CJGAVSoundPitchUncle:
            pitch = 0.8;
            break;
        case CJGAVSoundPitchGirl:
            pitch = 1.5;
            break;
        case CJGAVSoundPitchLolita:
            pitch = 2.0;
            break;
        default:
            pitch = 1.0;
            break;
    }
    return pitch;
}

/**
 * 获取变声系数 [变调设置将失效]
 * @param speedMode 设定的变声类型
 */
- (float)getSpeed:(CJGAVSoundSpeedMode)speedMode;
{
    float speed;
    switch (speedMode) {
        case CJGAVSoundSpeedMode_Fast1:
            speed = 1.5;
            break;
        case CJGAVSoundSpeedMode_Fast2:
            speed = 2.0;
            break;
        case CJGAVSoundSpeedMode_Slow1:
            speed = 0.7;
            break;
        case CJGAVSoundSpeedMode_Slow2:
            speed = 0.5;
            break;
        default:
            speed = 1.0;
            break;
    }
    return speed;
}

#pragma mark -- public methods

#pragma mark - CJGAVAudioPitchEngineInterface

/**
 * 入列缓存
 * @param inputBuffer 输入缓存 （PCM）
 * @return 是否成功放入队列
 */
- (BOOL)processInputBuffer:(CMSampleBufferRef)inputBuffer;
{
    return [_audioPitch queueInputBuffer:inputBuffer];
}

/**
 入列缓存结束调用
 @return 是否已处理
 */
- (BOOL)processInputBufferEnd;
{
    return [_audioPitch queueEOS];
}
/**
 * 音频数据处理完成
 * @param outputBuffer 应用特效后的音频数据 （PCM）
 */
- (void)processOutputBuffer:(CMSampleBufferRef)outputBuffer;
{
    
}

/** 改变输入采样格式
 * @param inputInfo 输入信息
 */
- (void)changeInputAudioInfo:(CJGAVAudioTrackInfo *)inputInfo;
{
    _audioPitch.inputInfo = inputInfo;
}

/**
 * 释放变调器
 */
- (void)destory;
{
    [_audioPitch destory];
}

/**
 * 重置变调、变速参数
 */
- (void)reset;
{
    [_audioPitch reset];
    _pitchType = CJGAVSoundPitchNormal;
    _speedMode = CJGAVSoundSpeedMode_Normal;
    _speed = 1.0;
    _pitch = 1.0;
}

/**
 * 刷新数据
 */
- (void)flush;
{
    [_audioPitch flush];
}


#pragma mark - CJGAVAudioPitchFactorySyncInterface
/**
 * 处理后的音频数据返回
 * @param output 变调变速后的音频数据
 * @param autoRelease 是否释放音频数据，默认为NO
 * since v3.0
 */
- (void)syncAudioPitchOutputBuffer:(CMSampleBufferRef)output autoRelease:(BOOL *)autoRelease;
{
    //输出buffer处理
    [self processOutputBuffer:output];
    //同步协议回调
    [self.delegate pitchEngine:self syncAudioPitchOutputBuffer:output autoRelease:autoRelease];
}

@end
