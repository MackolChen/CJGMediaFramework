//
//  CJGAVCoreBase.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVCoreBase.h"
#import "CJGAVRecordCoreBaseInterface.h"

NS_ASSUME_NONNULL_BEGIN

/**
 时间戳
 */
#define CJG_NOW (CACurrentMediaTime()*1000)

/**
 音视频录制的基础类
 */
@interface CJGAVRecordCoreBase : CJGAVCoreBase<CJGAVRecordCoreBaseInterface>
{
    
    NSTimer *_recordTimer;//录制定时器
    NSTimeInterval _recordTime;//录制时长
    BOOL _isRecording;// 是否正在录制中
    BOOL _isPaused;// 是否暂停
}

/**
 代理
 */
@property (nonatomic,weak) id<CJGAVRecordCoreBaseDelegate> delegate;

/**
 是否正在录制中
 */
@property (readonly, getter=isRecording) BOOL isRecording;


/**
 是否暂停
 */
@property (readonly, getter=isPaused) BOOL isPaused;


@end

NS_ASSUME_NONNULL_END
