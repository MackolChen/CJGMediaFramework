//
//  CJGAVAudioEncoderoptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/2.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecorderOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 音频码率(默认为96Kbps)
 */
typedef NS_ENUM (NSUInteger, CJGAVAACAudioBitRate)
{
    CJGAVAACAudioBitRate_32Kbps = 32000,
    
    CJGAVAACAudioBitRate_48Kbps = 48000,
    
    CJGAVAACAudioBitRate_64Kbps = 64000,
    
    CJGAVAACAudioBitRate_96Kbps = 96000,
    
    CJGAVAACAudioBitRate_128Kbps = 128000,
    
    CJGAVAACAudioBitRate_Default = CJGAVAACAudioBitRate_96Kbps
};

/**
 采样率 (默认为44.1Hz)
 */
typedef NS_ENUM (NSUInteger, CJGAVAACAudioSampleRate)
{
    
    CJGAVAACAudioSampleRate_16000Hz = 16000,

    CJGAVAACAudioSampleRate_22050Hz = 22050,
    
    CJGAVAACAudioSampleRate_32000Hz = 32000,

    CJGAVAACAudioSampleRate_44100Hz = 44100,
    
    CJGAVAACAudioSampleRate_48000Hz = 48000,
    
    CJGAVAACAudioSampleRate_Default = CJGAVAACAudioSampleRate_32000Hz
};

/**
 音频质量（VideoQuality_Default为默认配置）
 */
typedef NS_ENUM (NSUInteger,  CJGAVAACAudioQuality)
{
    CJGAVAACAudioQuality_min = 0,
    
    CJGAVAACAudioQuality_Low = 1,
    
    CJGAVAACAudioQuality_Medium = 2,
    
    CJGAVAACAudioQuality_High = 3,
    
    CJGAVAACAudioQuality_Max = 4,
    
    CJGAVAACAudioQuality_Default =  CJGAVAACAudioQuality_Medium
};


/**
 音频编码器的配置类
 */
@interface CJGAVAACEncodeOptions : CJGAVRecorderOptions<NSCoding, NSCopying>

/**
 音频配置
 
 @param audioQuality 音频质量
 */
+ (instancetype)defaultOptionsForQuality:(CJGAVAACAudioQuality)audioQuality;

/**
 音频配置
 
 @param audioQuality 音频质量
 @param channels 声道数
 */
+ (instancetype)defaultOptionsForQuality:(CJGAVAACAudioQuality)audioQuality channels:(NSInteger)channels;

#pragma mark - Attribute

/**
 声道数目(默认为1)
 */
@property (nonatomic, assign) NSUInteger numberOfChannels;

/**
 采样的位数
 */
@property (nonatomic, assign) NSUInteger bitsPerChannel;

/**
 采样率
 */
@property (nonatomic, assign) CJGAVAACAudioSampleRate audioSampleRate;

/**
 码率
 */
@property (nonatomic, assign) CJGAVAACAudioBitRate audioBitRate;

/**
 编码音频头
 */
@property (nonatomic, assign, readonly) char *asc;

/**
 音频数据长度
 */
@property (nonatomic, assign,readonly) NSUInteger bufferLength;


@end

NS_ASSUME_NONNULL_END
