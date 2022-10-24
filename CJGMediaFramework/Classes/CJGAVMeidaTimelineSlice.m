//
//  CJGAVTimeSlice.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/20.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMeidaTimelineSlice.h"

@interface CJGAVMeidaTimelineSlice(){
    // 根据速率调整时间时的对应Scale 默认：1.0
    CGFloat _adjustScale;
}
@end

@implementation CJGAVMeidaTimelineSlice

#pragma mark - setter getter
- (void)setSpeedMode:(CJGAVRecordSpeedMode)speedMode;
{
    _speedMode = speedMode;
    switch (speedMode) {
        case CJGAVRecordSpeedMode_Slow1:
            _adjustScale = 1.5;
            break;
        case CJGAVRecordSpeedMode_Slow2:
            _adjustScale = 2.0;
            break;
        case CJGAVRecordSpeedMode_Fast1:
            _adjustScale = 0.7;
            break;
        case CJGAVRecordSpeedMode_Fast2:
            _adjustScale = 0.5;
            break;
        default:
            break;
    }
}

- (CMTime)adjustedTime;
{
    if (!CMTIME_IS_VALID(self.end) || !CMTIME_IS_VALID(self.start)) return kCMTimeZero;
    
    CMTime duration = CMTimeSubtract(self.end, self.start);
    return CMTimeMake(duration.value * _adjustScale, duration.timescale);
}

/**
 设置默认参数配置
 */
- (void)setConfig;
{
    _speedMode = CJGAVRecordSpeedMode_Normal;
    _adjustScale = 1.0;
}

@end
