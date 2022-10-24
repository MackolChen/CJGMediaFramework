//
//  CJGAVRecodeOptions.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/12.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecorderOptions.h"

@implementation CJGAVRecorderOptions

+ (instancetype)defaultOptions{
    return [super defaultOptions];
}

/**
 设置默认参数配置(可以重置父类的默认参数，不设置的话，父类的默认参数会无效)
 */
- (void)setConfig;
{
    [super setConfig];
    
    _recordStatus = CJGAVRecordStateUnKnow;
    _recordMode = CJGAVRecordModeNormal;
    _recordSpeedMode = CJGAVRecordSpeedMode_Normal;
    
    _minRecordDelay = 3;
    _maxRecordDelay = -1;
}


@end
