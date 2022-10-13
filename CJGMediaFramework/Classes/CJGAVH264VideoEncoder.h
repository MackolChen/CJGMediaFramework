//
//  CJGAVH264VideoEcoder.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CJGAVH264VideoEncoderInterface.h"

NS_ASSUME_NONNULL_BEGIN

/**
 硬编码：视频编码器
 */
@interface CJGAVH264VideoEncoder : NSObject<CJGAVH264VideoEncoderInterface>
{
    CJGAVH264EncodeOptions *_options;
}
/**
 视频配置项
 */
@property (nonatomic, strong , readonly) CJGAVH264EncodeOptions *options;

/**
 代理
 */
@property (nonatomic, weak) id<CJGAVH264VideoEncoderDelegate> encodeDelegate;

@end

NS_ASSUME_NONNULL_END
