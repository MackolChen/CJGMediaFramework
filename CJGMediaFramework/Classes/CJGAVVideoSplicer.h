//
//  CJGAVVideoSplicer.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/8/15.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVCoreBase.h"
#import "CJGAVVideoSplicerOptions.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CJGAVVideoSplicerDelegate;

/**
 视频拼接工具
 
 功能 (建议拼接的视频的方向与分辨率尽量一致)
 1、将多个视频的片段进行拼接
 
 */
@interface CJGAVVideoSplicer : CJGAVCoreBase

// 代理设置
@property (nonatomic, weak) id<CJGAVVideoSplicerDelegate> spliceDelegate;

// 设置拼接参数options，如：视频输出路径、视频的总时长等
@property (nonatomic,strong) CJGAVVideoSplicerOptions  *spliceOptions;

// 需要进行合并的视频，合并顺序按照数组顺序
@property (nonatomic, strong) NSArray<CJGAVVideoSplicerOptions *> *videos;

/**
 初始化视频拼接器，用init初始化也可以，需要另外配置videos
 
 @param spliceOptions 拼接多视频的配置项
 @return CJGAVVideoSplicer
 */
- (instancetype)initWithSplicerOptions:(CJGAVVideoSplicerOptions *)spliceOptions;

/**
 初始化视频拼接器，用init初始化也可以，需要另外配置videos
 
 @param videos 多视频
 @return CJGAVVideoSplicer
 */
- (instancetype)initWithSplicerVideos:(NSArray <CJGAVVideoSplicerOptions *> *)videos;

/**
 * 开始合并视频操作
 */
- (void)startSplicing;

/**
 * 开始合并视频操作 block回调
 */
- (void)startSplicingWithCompletionHandler:(void (^ _Nullable)(NSString *filePath, CJGAVSpliceStatus status))handler;

/**
 * 取消合并操作
 */
- (void)cancelSplicing;

@end


#pragma mark - protocol CJGAVVideoSplicerDelegate

/**
 视频拼接代理
 */
@protocol CJGAVVideoSplicerDelegate <NSObject>

@optional

/**
 状态通知代理
 
 @param status 一个/多个视频拼接状态
 @param videoSplicer 视频拼接器
 */- (void)didSplicingVideoStatusChanged:(CJGAVSpliceStatus)status onVideoSplice:(CJGAVVideoSplicer *)videoSplicer;


/**
 所有的拼接结果通知代理
 
 @param result 剪辑结果（如：包括地址输出）
 @param videoSplicer 视频拼接器
 */- (void)didSplicedVideoResult:(CJGAVVideoSplicerOptions *)result onVideoSplice:(CJGAVVideoSplicer *)videoSplicer;

/**
 拼接完成:结果回调
 @param filePath 拼接结果文件路径
 @param videoSplicer 视频拼接器
 */
- (void)didCompletedSpliceVideoOutputFilePath:(NSString *)filePath onVideoSplice:(CJGAVVideoSplicer *)videoSplicer;

/**
 多视频拼接进度通知代理
 
 @param progress 剪辑进度
 @param videoSplicer 视频拼接器
 */
- (void)didSplicingVideoProgressChanged:(CGFloat)progress onVideoSplice:(CJGAVVideoSplicer *)videoSplicer;

/**
 拼接完成：拼接的媒体总时间回调
 @param mediaTotalTime 音视频的总时长
 @param videoSplicer 视频拼接器
 */
- (void)didCompletedSpliceMediaTotalTime:(NSTimeInterval)mediaTotalTime onVideoSplice:(CJGAVVideoSplicer *)videoSplicer;

@end

NS_ASSUME_NONNULL_END
