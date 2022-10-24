//
//  CJGAVRTMPFrame.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/24.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
 RTMP 数据包结构
 */
@interface CJGAVRTMPFrame : NSObject

/**
 时间戳
 */
@property (nonatomic, assign) uint64_t timestamp;

/**
 RTMP 数据包
 */
@property (nonatomic, strong) NSData *data;

/**
 RTMP 包头
 */
@property (nonatomic, strong) NSData *header;

@end

NS_ASSUME_NONNULL_END
