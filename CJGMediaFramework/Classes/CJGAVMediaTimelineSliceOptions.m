//
//  CJGAVMediaTimelineSliceOptions.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMediaTimelineSliceOptions.h"

@implementation CJGAVMediaTimelineSliceOptions

+ (instancetype)defaultOptions{
    return [super defaultOptions];
}

/**
 设置默认参数配置(可以重置父类的默认参数，不设置的话，父类的默认参数会无效)
 */
- (void)setConfig{
    [super setConfig];
    
    _enableCreateFilePath = NO;
    _status = CJGAVMediaTimelineSliceCompositionStatusUnknown;
}


@end
