//
//  CJGAVThreeAudioRecorder.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/8.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecordAudioCoreBase.h"

NS_ASSUME_NONNULL_BEGIN

/**
 音频录制器：通过组件示例AudioComponentInstance形式获取的音频数据Data格式
 */
@interface CJGAVThreeAudioRecorder : CJGAVRecordAudioCoreBase

/**
 *  开启音频采集
 */
@property (nonatomic, assign) BOOL enableAudioCapture;

/**
 *  是否静音(默认不开启静音）
 */
@property (nonatomic, assign) BOOL muted;

@end

NS_ASSUME_NONNULL_END
