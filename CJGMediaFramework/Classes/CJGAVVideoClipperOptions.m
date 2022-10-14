//
//  CJGAVVideoClipperOptions.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/8/2.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVVideoClipperOptions.h"

@implementation CJGAVVideoClipperOptions

+ (instancetype)defaultOptions{
    return [super defaultOptions];
}

/**
 设置默认参数配置(可以重置父类的默认参数，不设置的话，父类的默认参数会无效)
 */
- (void)setConfig{
    
    [super setConfig];
    
    _meidaType = CJGAVMediaTypeVideo;
    _outputFileType = CJGAVVideoOutputFileTypeQuickTimeMovie;
    _appOutputFileType = AVFileTypeQuickTimeMovie;
    _saveSuffixFormat = @"mov";
    _outputFileName = @"videoClipFile";
}

@end
