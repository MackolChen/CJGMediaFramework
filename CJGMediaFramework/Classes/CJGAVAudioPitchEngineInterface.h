//
//  CJGAVAudioPitchEngineInterface.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/17.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 音频特效处理引擎协议
 */
@protocol CJGAVAudioPitchEngineInterface <NSObject>

/**
 将 PCM 裸流放入 CJGAVAudioPitchEngine 队列，等待处理。
 @param inputBuffer 输入缓存 （PCM）
 @return 是否已处理
 */
- (BOOL)processInputBuffer:(CMSampleBufferRef)inputBuffer;

/**
 入列缓存结束调用
 @return 是否已处理
 */
- (BOOL)processInputBufferEnd;

/**
 音频数据处理完成
 @param outputBuffer 应用特效后的音频数据 （PCM）
 */
- (void)processOutputBuffer:(CMSampleBufferRef)outputBuffer;

/** 改变输入采样格式
 * @param inputInfo 输入信息
 */
- (void)changeInputAudioInfo:(CJGAVAudioTrackInfo *)inputInfo;

/**
 释放 CJGAVAudioPitchEngine
 */
- (void)destory;

/**
 重置 Engine
 */
- (void)reset;

/**
 刷新数据
 */
- (void)flush;

@end

NS_ASSUME_NONNULL_END
