//
//  CJGAVCoreBase.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecordCoreBase.h"

@implementation CJGAVRecordCoreBase

#pragma mark --  定时器
//添加定时器
- (void)addRecordTimer;
{
    if (!_recordTimer) {
        
        _recordTime = 0;

        /**
         两种方式创建定时器
         step1:scheduledTimerWithTimeInterval，会默认将定时器加入到NSRunLoopCommonModes
         */
        //_recordTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(recordTimerAction) userInfo:nil repeats:YES];
        /**
         step2:
         */
        _recordTimer = [NSTimer timerWithTimeInterval:1.0 target:self selector:@selector(recordTimerAction) userInfo:nil repeats:YES];
        [[NSRunLoop mainRunLoop] addTimer:_recordTimer forMode:NSRunLoopCommonModes];
        
        /**
         以上两个方法都有缺陷：存在延时的风险
         如果此RunLoop正在执行一个连续性的运算，timer就会被延时出发。重复性的timer遇到这种情况
         如果延迟超过了一个周期，则会在延时结束后立刻执行，并按照之前指定的周期继续执行。
         */
    }
}

    

//定时器事件
- (void)recordTimerAction;
{
    _recordTime ++;
    if (self.delegate && [self.delegate respondsToSelector:@selector(didRecordedChangedCurrentTotalTimeLength:)]) {
        [self.delegate didRecordedChangedCurrentTotalTimeLength:_recordTime];
    }
    //NSLog(@"++++++++>>>%ld",(long)self.recordTime);
}

//移除定时器
- (void)removeRecordTimer;
{
    [_recordTimer invalidate];
    _recordTimer = nil;
}


- (void)startRecord{
    
}

- (void)pauseRecord{
    
}

- (void)stopRecord{
    
}

- (void)reRecording{
    
}

/**
 设置回调通知，并委托协议
 
 @param state 回调的录制状态
 */
- (void)notifyRecordState:(CJGAVRecordState)state;
{
    
}

- (void)dealloc{
    
    [self removeRecordTimer];
    [self destory];
}

@end
