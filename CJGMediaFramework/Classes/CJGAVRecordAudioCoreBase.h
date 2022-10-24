//
//  CJGAVRecordAudioCoreBase.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecordCoreBase.h"

NS_ASSUME_NONNULL_BEGIN
/**
 音频录制的基础类
 */
@interface CJGAVRecordAudioCoreBase : CJGAVRecordCoreBase<CJGAVAudioRecorderInterface>
{
    CJGAVAudioRecorderOptions *_options;
}

/**
 音频配置项
 */
@property (nonatomic, strong) CJGAVAudioRecorderOptions *options;

/**
 audioSession的处理来电、锁屏、启动其他音频app等类别
 */
@property (nonatomic, assign) AVAudioSessionCategory sessionCategory;

/**
 代理
 */
@property (nonatomic, weak) id<CJGAVAudioRecorderDelegate> delegate;


#pragma mark -- 激活Session控制当前的使用场景
/**
 *  初始化音频检查
 */
- (void)setAudioSession;

/**
 重置音频会话分类
 */
- (void)resetAudioSessionCategory;


@end

NS_ASSUME_NONNULL_END
