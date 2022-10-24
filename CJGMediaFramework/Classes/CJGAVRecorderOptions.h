//
//  CJGAVRecodeOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/12.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 录制模式
 */
typedef NS_ENUM(NSInteger,CJGAVRecordMode)
{
    /** 正常模式 */
    CJGAVRecordModeNormal,
    
    /** 续拍模式 */
    CJGAVRecordModeKeep,
};

/**
 录制状态
 */
typedef NS_ENUM(NSInteger, CJGAVRecordState) {
    
    CJGAVRecordStateReadyToRecord = 0, //开始录制
    CJGAVRecordStateRecording,         //正在录制
    CJGAVRecordStatePause,             //暂停录制
    CJGAVRecordStateResume,            //继续录制
    CJGAVRecordStateCompleted,         //完成录制
    CJGAVRecordStateCanceled,          //取消录制
    CJGAVRecordStateFailed,            //录制失败
    
    CJGAVRecordStateLessMinRecordTime, //小于最小录制时间
    CJGAVRecordStateMoreMaxRecordTime, //大于等于最大录制时间
    
    CJGAVRecordStateSaving,            //正在保存
    CJGAVRecordStateSavingCompleted,   //保存完成
    CJGAVRecordStateUnKnow             //录制时，发生未知原因
};

/**
 录制速度模式
 */
typedef NS_ENUM(NSInteger,CJGAVRecordSpeedMode)
{
    /** 标准模式 速度大小1.0 */
    CJGAVRecordSpeedMode_Normal,
    
    /** 快速模式 速度大小1.5 */
    CJGAVRecordSpeedMode_Fast1,
    
    /** 极快模式 速度大小2.0 */
    CJGAVRecordSpeedMode_Fast2,
    
    /** 慢速模式 速度大小0.7 */
    CJGAVRecordSpeedMode_Slow1,
    
    /** 极慢模式  速度大小0.5 */
    CJGAVRecordSpeedMode_Slow2,
};

/**
 音视频录制的基础配置类
 */
@interface CJGAVRecorderOptions : CJGAVOptions
{
    NSUInteger _minRecordDelay;
    NSUInteger _maxRecordDelay;
    CJGAVRecordState _recordStatus;
    CJGAVRecordMode _recordMode;
    CJGAVRecordSpeedMode _recordSpeedMode;
    NSTimeInterval _outputDuration;
}

/**
 最小录制时间，默认3s,
 */
@property (nonatomic, assign) NSUInteger minRecordDelay;

/**
 最大录制时长， 默认: -1 不限制录制时长 单位: 秒
 */
@property (nonatomic, assign) NSUInteger maxRecordDelay;

/**
 录制状态
 */
@property (nonatomic, assign, getter=recordStatus) CJGAVRecordState recordStatus;

/**
 录制模式：默认正常
 */
@property (nonatomic, assign) CJGAVRecordMode recordMode;

/**
 录制变速模式：默认正常模式
 */
@property (nonatomic, assign) CJGAVRecordSpeedMode recordSpeedMode;

/**
 已录制的总时长
 */
@property (nonatomic, assign,getter=outputDuration) NSTimeInterval outputDuration;


@end

NS_ASSUME_NONNULL_END
