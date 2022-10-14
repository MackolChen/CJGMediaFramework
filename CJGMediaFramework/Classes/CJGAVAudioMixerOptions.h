//
//  CJGAVAudioMixerOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/8/2.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMixerOptions.h"
#import "CJGAVEncodeAudioSetting.h"

NS_ASSUME_NONNULL_BEGIN

@interface CJGAVAudioMixerOptions : CJGAVMixerOptions

/** 音频编码设置*/
@property (nonatomic,strong) CJGAVEncodeAudioSetting *audioSetting;

@end

NS_ASSUME_NONNULL_END
