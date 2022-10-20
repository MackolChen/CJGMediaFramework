//
//  CJGAVH264VideoEncoderInterface.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/24.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CJGAVH264EncodeOptions.h"
#import "CJGAVVideoRTMPFrame.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CJGAVH264VideoEncoderInterface;

@protocol CJGAVH264VideoEncoderDelegate <NSObject>

@optional
/**
 编码器编码过程中编码回调
 
 @param frame 编码后的数据
 @param encoder 编码器
 */
- (void)didEncordingStreamingBufferFrame:(CJGAVVideoRTMPFrame *)frame encoder:(id<CJGAVH264VideoEncoderInterface>)encoder;

@end


/**
 视频编码器的委托协议（约束）
 */
@protocol CJGAVH264VideoEncoderInterface <NSObject>

@required
/**
 编码:给视频buffer数据进行编码
 
 @param pixelBuffer 视频数据
 @param timeStamp 时间戳
 */
- (void)encodeVideoData:(CVPixelBufferRef)pixelBuffer timeStamp:(uint64_t)timeStamp;

@optional

/**
 码率
 */
@property (nonatomic, assign) NSInteger videoBitRate;

/**
 帧率
 */
@property (nonatomic, assign) NSInteger videoFrameRate;

/**
 初始化配置
 
 @param options 配置
 @return options
 */
- ( instancetype)initWithVideoStreamOptions:(CJGAVH264EncodeOptions *)options;


/**
 停止编码
 */
- (void)stopEncoder;

@end

NS_ASSUME_NONNULL_END
