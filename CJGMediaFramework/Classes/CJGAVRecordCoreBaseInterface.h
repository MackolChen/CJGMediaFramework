//
//  CJGAVRecordCoreBaseInterface.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/26.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CJGAVVideoRecorderOptions.h"
#import "CJGAVAudioRecorderOptions.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CJGAVRecordCoreBaseInterface;

@protocol CJGAVRecordCoreBaseDelegate <NSObject>

@optional

/**
 在录制音视频是添加定时器，定时事件回调

 @param recordTimeLength 录制的时间
 */
- (void)didRecordedChangedCurrentTotalTimeLength:(NSTimeInterval)recordTimeLength;

/**
 音视频录制状态回调通知代理(所有的音视频录制关于状态的回调都调用这个)

 @param status 录制状态
 @param recorder 当前录制音视频录制器
 */
- (void)didRecordingStatusChanged:(CJGAVRecordState)status recorder:(id<CJGAVRecordCoreBaseInterface>)recorder;

/**
 录制完成
 @param filePath 录制结果文件路径
 @param recorder 录制器对象
 */
- (void)didCompletedOutputFilePath:(NSString *)filePath recorder:(id<CJGAVRecordCoreBaseInterface>)recorder;

/**
 录制完成：录制时间回调
 @param recordDuration 已录制的总时间
 @param recorder 录制器对象
 */
- (void)didCompletedOutputDuration:(NSTimeInterval)recordDuration recorder:(id<CJGAVRecordCoreBaseInterface>)recorder;

@end

@protocol CJGAVRecordCoreBaseInterface <NSObject>

@optional

//添加录制定时器
- (void)addRecordTimer;

//录制定时事件
- (void)recordTimerAction;

//移除定时器
- (void)removeRecordTimer;

/**
 录制时间是否超过最大录制时间
 */
- (BOOL)isMoreRecordTime;

/**
 录制时间是否小于最小录制时间
 */
- (BOOL)isLessRecordTime;

/**
 开始录制
 */
- (void)startRecord;

/**
 暂停录制
 */
- (void)pauseRecord;

/**
 结束录制
 */
- (void)stopRecord;

/**
 重新录制
 */
- (void)reRecording;

/**
 取消录制
 */
- (void)cancelRecord;

/**
 设置回调通知，并委托协议
 
 @param state 回调的录制状态
 */
- (void)notifyRecordState:(CJGAVRecordState)state;

@end


@protocol CJGAVVideoRecorderInterface;

@protocol CJGAVVideoRecorderDelegate <NSObject,CJGAVRecordCoreBaseDelegate>

@optional

/**
 视频录制：通知委托已写入新的视频帧。
 
 @param sampleBuffer 视频帧
 @param videoRecorder 录制器
 */
- (void)didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromVideoRecorder:(id<CJGAVVideoRecorderInterface>)videoRecorder;

@end

@protocol CJGAVVideoRecorderInterface <NSObject,CJGAVRecordCoreBaseInterface>

@optional

/**
 初始化配置
 
 @param options 配置
 @return options
 */
- ( instancetype)initWithVideoRecordOptions:(CJGAVVideoRecorderOptions *)options;

/**
 将设备捕捉到的画面呈现到某个view上
 
 @param view 显示具体捕捉画面的视图
 */
- (void)showCaptureSessionOnView:(UIView *)view;

/**
 告诉接收器开始运行。
 */
- (void)startRunning;

/**
 告诉接收器停止运行。
 */
- (void)stopRunning;

//切换设备的摄像机位置
- (void)switchCameraDevicePosition;

@end


@protocol CJGAVAudioRecorderInterface;

@protocol CJGAVAudioRecorderDelegate <NSObject,CJGAVRecordCoreBaseDelegate>

@optional

/**
 音频录制的结果通知代理，试用与所有的音频录制器

 @param result 结果
 @param recorder 当前音频录制器
 */
- (void)didRecordedAudioResult:(CJGAVAudioRecorderOptions *)result recorder:(id<CJGAVAudioRecorderInterface>)recorder;

/**
 
 CJGAVFirstAudioRecorder的委托
 音频的声波监控，录制时，声波波动值，可以根据该值进行声波UI刷新
 @param progress 声波波动值
 */
- (void)didChangedAudioRecordingPowerProgress:(CGFloat)progress;

/**
 CJGAVSecondAudioRecorder的委托
 音频录制：通知委托已写入新的视频帧。
 
 @param sampleBuffer 视频帧
 @param audioRecorder 录制器
 */
- (void)didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromAudioRecorder:(id<CJGAVAudioRecorderInterface>)audioRecorder;

/**
 CJGAVThreeAudioRecorder的委托
 编码器编码过程回调
 
 @param data 录制的音频数据
 @param recorder CJGAVThreeAudioRecorder
 */
- (void)didRecordingAudioData:(NSData *)data recorder:(id<CJGAVAudioRecorderInterface>)recorder;

@end

@protocol CJGAVAudioRecorderInterface <NSObject,CJGAVRecordCoreBaseInterface>

@optional

/**
 初始化配置
 
 @param options 配置
 @return options
 */
- ( instancetype)initWithAudioRecordOptions:(CJGAVAudioRecorderOptions *)options;

#pragma mark -- 媒体写入
/**
 媒体写入器audioWriter开始写入
 */
- (void)startWriting;

/**
 媒体写入器audioWriter取消写入
 */
- (void)cancelWriting;

/**
 设置回调通知，并委托协议
 
 @param recoderOptions 回调的录制结果
 */
- (void)notifyRecordResult:(CJGAVAudioRecorderOptions *)recoderOptions;

@end

NS_ASSUME_NONNULL_END
