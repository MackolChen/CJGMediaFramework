//
//  CJGAVAudioMixer.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/12.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVCoreBase.h"
#import "CJGAVAudioMixerOptions.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CJGAVAudioMixerDelegate;

/**
 多音频混合
 
 功能：
 1、将一个音频(可设定时间范围)，与一个音频(可设定时间范围)混合
 2、将一个音频(可设定时间范围)，与多个音频(可设定时间范围)混合
 3、导出一个视频中的音轨
 
 注意：该多音轨混合器，合成的开始时间节点、结束时间、时间范围都是以主音轨为准。
 */
@interface CJGAVAudioMixer : CJGAVCoreBase

// 代理
@property (nonatomic, weak) id<CJGAVAudioMixerDelegate> mixDelegate;

// 主音频，即背景音频，在混合过程中，主音频不变
@property (nonatomic, strong) CJGAVAudioMixerOptions *mainAudio;

// 混合音频，即要添加在主音频上混合音频
@property (nonatomic, strong) NSArray<CJGAVAudioMixerOptions *> *mixAudios;

/**
 初始化音频混合器，用init初始化也可以，mainAudio都得自行配置
 
 @param mainAudio 主音轨
 @return CJGAVAudioMixer
 */
- (instancetype)initWithMixerAudioOptions:(CJGAVAudioMixerOptions *)mainAudio;

/**
 开始混合音轨，该方法的混合音轨结果没有block回调过程，结果可通过协议拿到
 */
- (void)startMixingAudio;

/**
 开始混合音轨，该方法的混合音轨结果有block回调，同时也可通过协议拿到
 */
- (void)startMixingAudioWithCompletion:(void (^ _Nullable)(NSString*, CJGAVMixStatus))handler;

/**
 取消混合操作
 */
- (void)cancelMixing;

@end

#pragma mark - protocol CJGAVAudioMixerDelegate

/**
 多音频混合代理
 */
@protocol CJGAVAudioMixerDelegate <NSObject>

@optional

// 状态通知代理
- (void)didMixingAudioStatusChanged:(CJGAVMixStatus)audioStatus onAudioMix:(CJGAVAudioMixer *)audioMixer;

// 结果通知代理
- (void)didMixedAudioResult:(CJGAVMixerOptions *)result onAudioMix:(CJGAVAudioMixer *)audioMixer;

// 混合完成路径通知代理
- (void)didCompletedMixAudioOutputPath:(NSString *)outputPath onAudioMix:(CJGAVAudioMixer *)audioMixer;
@end


NS_ASSUME_NONNULL_END
