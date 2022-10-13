//
//  CJGAVAACAudioEncoderInterface.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/2.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CJGAVAACEncodeOptions.h"
#import "CJGAVAudioRTMPFrame.h"

NS_ASSUME_NONNULL_BEGIN
@protocol CJGAVAACAudioEncoderInterface;
@protocol CJGAVAACAudioEncoderDelegate <NSObject>

/**
 编码器编码过程回调
 
 @param frame 数据
 @param encoder 编码器
 */
- (void)didEncordingStreamingBufferFrame:(CJGAVAudioRTMPFrame *)frame encoder:(id<CJGAVAACAudioEncoderInterface>)encoder;


@end

@protocol CJGAVAACAudioEncoderInterface <NSObject>

/**
 初始化音频配置
 
 @param options 音频配置
 @return CJGAVAACAudioEncoder
 */
- (instancetype)initWithAudioStreamOptions:(CJGAVAACEncodeOptions *)options;


@end

NS_ASSUME_NONNULL_END
