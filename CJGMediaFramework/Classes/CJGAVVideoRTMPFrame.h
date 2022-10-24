//
//  CJGAVH264VideoRTMPFrame.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/24.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRTMPFrame.h"

NS_ASSUME_NONNULL_BEGIN
/**
 视频数据
 */
@interface CJGAVVideoRTMPFrame : CJGAVRTMPFrame

/**
 是否关键帧
 */
@property (nonatomic, assign) BOOL isKeyFrame;

/**
 序列的参数集
 */
@property (nonatomic, strong) NSData *sps;

/**
 图像的参数集
 */
@property (nonatomic, strong) NSData *pps;

@end

NS_ASSUME_NONNULL_END
