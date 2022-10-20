//
//  CJGAVAudioPitchEngineRecorder.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/18.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecordAudioCoreBase.h"
#import "CJGAVMediaTimelineSliceComposition.h"
#import "CJGAVAudioPitchEngineRecorderOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 音频录制
 支持变声及快慢速调节
 */
@interface CJGAVAudioPitchEngineRecorder : CJGAVRecordAudioCoreBase

/**
 音频变掉录制器配置项
 */
@property (nonatomic, strong) CJGAVAudioPitchEngineRecorderOptions *pitchOptions;

/**
 删除最后一个音频片段
 */
- (void)deleteLastAudioFragment;

- (instancetype)initWithAudioPitchEngineRecordOptions:(CJGAVAudioPitchEngineRecorderOptions *)pitchOptions;

@end

NS_ASSUME_NONNULL_END
