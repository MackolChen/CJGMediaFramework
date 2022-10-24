//
//  CJGAVComponent.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>

/**文件管理类，任意操作Documents、Cache、Library中的文件*/
#import "CJGAVFileManager.h"
/**关于访问麦克风、相机、相册、地理位置权限设置*/
#import "CJGAVDeviceAthorizationSettings.h"
/**消息转发简单处理，解决循环引用，如：NSTimer*/
#import "CJGProxy.h"
/**日志处理类*/
#import "CJGAVLog.h"
/**CMSampleBufferRef 助手*/
#import "CJGAVMediaSampleBufferAssistant.h"

/**音频录制器*/
#import "CJGAVFirstAudioRecorder.h"
/**音频录制器*/
#import "CJGAVSecondAudioRecorder.h"
/**音频录制器*/
#import "CJGAVThreeAudioRecorder.h"
/**音频音调（变调、变速）录制器*/
#import "CJGAVAudioPitchEngineRecorder.h"
/**音频音调（变调、变速）引擎*/
#import "CJGAVAudioPitchEngine.h"

/**音频播放器，alloc初始化的形式*/
#import "CJGAVAudioPlayer.h"
/**音频播放器，单例类的形式*/
#import "CJGAVSingleAudioPlayer.h"

/**音频编码器*/
#import "CJGAVAACAudioEncoder.h"
/**音频解码器*/
#import "CJGAVAACAudioDecoder.h"

/**音频混合器*/
#import "CJGAVAudioMixer.h"
/**音频剪辑器*/
#import "CJGAVAudioClipper.h"
/**音视频分段录制，对一个/多个时间切片进行编辑，调整时间线合成新的音视频*/
#import "CJGAVMediaTimelineSliceComposition.h"

/**视频录制器*/
#import "CJGAVFirstVideoRecorder.h"

/**视频编码器*/
#import "CJGAVH264VideoEncoder.h"
/**视频解码器*/
#import "CJGAVH246VideoDecoder.h"

/**音视频混合器*/
#import "CJGAVVideoMixer.h"
/**视频剪辑器*/
#import "CJGAVVideoClipper.h"
/**视频图片提取器*/
#import "CJGAVVideoImageExtractor.h"

/**视频拼接器*/
#import "CJGAVVideoSplicer.h"
/**音视频播放器，本地、网络播放*/
#import "CJGAVPlayer.h"



@interface CJGAVComponent : NSObject

/**
 *  设置日志输出级别
 *
 *  @param level 日志输出级别 (默认：CJGAVLogLevelFATAL 不输出)
 */
+ (void)setLogLevel:(CJGAVLogLevel)level;

@end
