//
//  CJGAVAudioRecorderOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/28.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecorderOptions.h"
#import "CJGAVEncodeAudioSetting.h"

NS_ASSUME_NONNULL_BEGIN

/**
 音频质量（VideoQuality_Default为默认配置）
 */
typedef NS_ENUM (NSUInteger,  CJGAVAudioRecordQuality)
{
    CJGAVAudioRecordQuality_min = 0,
    
    CJGAVAudioRecordQuality_Low = 1,
    
    CJGAVAudioRecordQuality_Medium = 2,
    
    CJGAVAudioRecordQuality_High = 3,
    
    CJGAVAudioRecordQuality_Max = 4,

    CJGAVAudioRecordQuality_Default =  CJGAVAudioRecordQuality_Medium
};

/**
 采样率 (默认为44.1Hz)
 */
typedef NS_ENUM (NSUInteger, CJGAVAudioRecordSampleRate)
{
    
    CJGAVAudioRecordSampleRate_16000Hz = 16000,
    
    CJGAVAudioRecordSampleRate_22050Hz = 22050,
    
    CJGAVAudioRecordSampleRate_32000Hz = 32000,
    //32000
    CJGAVAudioRecordSampleRate_44100Hz = 44100,
    
    CJGAVAudioRecordSampleRate_48000Hz = 48000,
    //96000
    CJGAVAudioRecordSampleRate_Default = CJGAVAudioRecordSampleRate_32000Hz
};

/**
 采样位数(默认为16d)
 */
typedef NS_ENUM (NSUInteger, CJGAVAudioRecordBitDepth)
{
    CJGAVAudioRecordBitDepth_8d  = 8,
    
    CJGAVAudioRecordBitDepth_16d = 16,
    
    CJGAVAudioRecordBitDepth_24d = 24,
    
    CJGAVAudioRecordBitDepth_32d = 32,
    
    CJGAVAudioRecordBitDepth_Default = CJGAVAudioRecordBitDepth_16d
};

/**
 音频码率(默认为64Kbps)
 */
typedef NS_ENUM (NSUInteger, CJGAVAudioRecordBitRate)
{
    CJGAVAudioRecordBitRate_32Kbps = 32000,
    
    CJGAVAudioRecordBitRate_48Kbps = 48000,

    CJGAVAudioRecordBitRate_64Kbps = 64000,
    
    CJGAVAudioRecordBitRate_96Kbps = 96000,
    
    CJGAVAudioRecordBitRate_128Kbps = 128000,
    
    CJGAVAudioRecordBitRate_Default = CJGAVAudioRecordBitRate_64Kbps
};

/**
 音频录制的参数配置项
 */
@interface CJGAVAudioRecorderOptions : CJGAVRecorderOptions
{
    CJGAVAudioRecordQuality _recordQuality;
    NSUInteger _audioChannels;
    CJGAVAudioRecordSampleRate _recordSampleRate;
    CJGAVAudioRecordBitDepth _recordBitDepth;
    CJGAVAudioRecordBitRate _recordBitRate;
    CJGAVEncodeAudioSetting *_audioSetting;
}

/**
 是否开启音频声波定时器,默认NO
 */
@property (nonatomic, assign) BOOL isAcousticTimer;

/** 音频质量（VideoQuality_Default为默认配置）*/
@property (nonatomic,assign) CJGAVAudioRecordQuality recordQuality;

/**音频的通道 声道数 1、2*/
@property (nonatomic,assign) NSUInteger audioChannels;

/** 采样率 (默认为44.1Hz)*/
@property (nonatomic,assign) CJGAVAudioRecordSampleRate recordSampleRate;

/** 采样率 (默认为采样位数(默认为16d))*/
@property (nonatomic,assign) CJGAVAudioRecordBitDepth recordBitDepth;

/** 比特率 (默认为64Kbps)*/
@property (nonatomic,assign) CJGAVAudioRecordBitRate recordBitRate;

/** 音频编码设置*/
@property (nonatomic,strong) CJGAVEncodeAudioSetting *audioSetting;

@end

NS_ASSUME_NONNULL_END
