//
//  CJGAVTimeSlice.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/20.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVTimeRange.h"
#import "CJGAVRecorderOptions.h"

NS_ASSUME_NONNULL_BEGIN

@interface CJGAVMeidaTimelineSlice : CJGAVTimeRange

// 该时间段速率  默认：CJGAVRecordSpeedMode_Normal
@property (nonatomic, assign) CJGAVRecordSpeedMode speedMode;

// 变速调整后对应的该片段时长
@property (nonatomic, assign, readonly) CMTime adjustedTime;

// 是否移除该段视频 默认：NO
@property (nonatomic, assign) BOOL isRemove;

@end

NS_ASSUME_NONNULL_END
