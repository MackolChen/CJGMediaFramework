//
//  CJGAVAudioRTMPFrame.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/4.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRTMPFrame.h"

NS_ASSUME_NONNULL_BEGIN
/**
 音频数据
 */
@interface CJGAVAudioRTMPFrame : CJGAVRTMPFrame

/**
 音频信息
 */
@property (nonatomic, strong) NSData *audioInfo;

@end

NS_ASSUME_NONNULL_END
