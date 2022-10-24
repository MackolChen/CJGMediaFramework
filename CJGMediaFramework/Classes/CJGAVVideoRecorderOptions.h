//
//  CJGAVVideoRecorderoptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/25.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecorderOptions.h"

NS_ASSUME_NONNULL_BEGIN

//录制视频的长宽比
typedef NS_ENUM(NSInteger, CJGAVVideoRecordViewType) {
    Type1X1 = 0,
    Type4X3,
    TypeFullScreen
};

//闪光灯状态
typedef NS_ENUM(NSInteger, CJGAVVideoRecordFlashState) {
    CJGAVVideoRecordFlashClose = 0,
    CJGAVVideoRecordFlashOpen,
    CJGAVVideoRecordFlashAuto,
};

//摄像头位置
typedef NS_ENUM(NSInteger, CJGAVVideoRecordPosition) {
    CJGAVVideoRecordPositionFront = 0,
    CJGAVVideoRecordPositionBack,
    CJGAVVideoRecordPositionUnspecified,
};

//控制录制的视频是否有声音
typedef NS_ENUM(NSInteger, CJGAVCJGAVVideoRecordVoiceType) {
    CJGAVVideoRecordVoiceTypeSoundType = 0,
    CJGAVVideoRecordVoiceTypeNoSoundType,
};


//录制视频的输出类型
typedef NS_ENUM(NSInteger,CJGAVVideoRecordOutputType) {
    CJGAVVideoRecordMovieFileOutput = 0,
    CJGAVVideoRecordVideoDataOutput,
};

/**
 视频分辨率
 */
typedef NS_ENUM (NSUInteger, CJGAVCaptureSessionPreset)
{
    
    CJGAVCaptureSessionPreset_Low = 0,
    
    CJGAVCaptureSessionPreset_Medium = 1,
    
    CJGAVCaptureSessionPreset_High = 2,
    
    CJGAVCaptureSessionPreset_Default =  CJGAVCaptureSessionPreset_High
};


/**
 视频录制的参数配置项
 */
@interface CJGAVVideoRecorderOptions : CJGAVRecorderOptions

/**
 视频录制的画面比例
 */
@property (nonatomic, assign) CJGAVVideoRecordViewType recordViewType;

/**
 录制的状态
 */
@property (nonatomic, assign) CJGAVRecordState recordState;

/**
 摄像头位置
 */
@property (nonatomic, assign) CJGAVVideoRecordPosition recordPosition;

/**
 是否有声音
 */
@property (nonatomic, assign) CJGAVCJGAVVideoRecordVoiceType recordVoiceType;

/**
 录制视频的输出类型
 */
@property (nonatomic, assign) CJGAVVideoRecordOutputType recordOutputType;

/**
 录制视频的分辨率
 */
@property (nonatomic, assign) CJGAVCaptureSessionPreset sessionPreset;

/**
 采集分辨率
 */
@property (nonatomic, copy) NSString *avSessionPreset;

/**
 摄像头位置
 */
@property (nonatomic, assign) AVCaptureDevicePosition devicePosition;


/**
 录制结束是否跳出预览视图
 */
@property (nonatomic, assign) BOOL isOutPreview;


/**
 视频配置(分辨率)
 
 @param sessionPreset 视频分辨率
 @return CJGAVVideoRecorderOptions
 */
+ (instancetype)defaultOptionsForSessionPreset:(CJGAVCaptureSessionPreset)sessionPreset;

/**
 视频配置(分辨率&摄像机位置设置)
 
 @param sessionPreset 视频分辨率
 @param videoRecordPosition 摄像机位置
 @return CJGAVVideoRecorderOptions
 */
+ (instancetype)defaultOptionsForSessionPreset:(CJGAVCaptureSessionPreset)sessionPreset videoRecordPosition:(CJGAVVideoRecordPosition)videoRecordPosition;

@end

NS_ASSUME_NONNULL_END
