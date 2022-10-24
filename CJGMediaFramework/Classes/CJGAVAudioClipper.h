//
//  CJGAVAudioCliper.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/14.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVCoreBase.h"
#import "CJGAVAudioClipperOptions.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CJGAVAudioClipperDelegate;

/**
 音频剪辑器
 */
@interface CJGAVAudioClipper : CJGAVCoreBase

// 代理
@property (nonatomic, weak) id<CJGAVAudioClipperDelegate> clipDelegate;

// 需要剪辑的音频素材
@property (nonatomic, strong) CJGAVAudioClipperOptions *clipAudio;

// 要删除的时间段数组,如果设置了需要删除的时间数组则以这个为主进行裁剪，如果没设置，则以atTimeRange来进行设置
@property (nonatomic, strong) NSArray<CJGAVTimeRange *> * deleteTimeRangeArr;

/**
 初始化音频剪辑器，用init初始化也可以，clipAudio都得自行配置
 
 @param clipAudio 需要裁剪的音轨
 @return CJGAVAudioCliper
 */
- (instancetype)initWithCliperAudioOptions:(CJGAVAudioClipperOptions *)clipAudio;

/**
 开始剪辑音轨，该方法的剪辑音轨结果没有block回调过程，结果可通过协议拿到
 */
- (void)startClippingAudio;

/**
 开始剪辑音轨，该方法的剪辑音轨结果有block回调，同时也可通过协议拿到
 */
- (void)startClippingAudioWithCompletion:(void (^ _Nullable)(NSString*, CJGAVClipStatus))handler;

/**
 取消剪辑操作
 */
- (void)cancelClipping;


@end

#pragma mark - protocol CJGAVAudioClipperDelegate

/**
 音频剪辑代理
 */
@protocol CJGAVAudioClipperDelegate <NSObject>

@optional

// 状态通知代理
- (void)didClippingAudioStatusChanged:(CJGAVClipStatus)audioStatus onAudioClip:(CJGAVAudioClipper *)audioClipper;

// 结果通知代理
- (void)didClipedAudioResult:(CJGAVAudioClipperOptions *)result onAudioClip:(CJGAVAudioClipper *)audioClipper;

// 剪辑完成路径通知代理
- (void)didCompletedClipAudioOutputPath:(NSString *)outputPath onAudioClip:(CJGAVAudioClipper *)audioMixer;
@end
NS_ASSUME_NONNULL_END
