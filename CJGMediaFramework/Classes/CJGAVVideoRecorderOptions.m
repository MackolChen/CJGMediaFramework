//
//  CJGAVVideoRecorderoptions.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/25.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVVideoRecorderOptions.h"

@implementation CJGAVVideoRecorderOptions
//必须走一下父类的方法；为了一些父类的默认参数生效
- (instancetype)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

/**
 默认视频配置
 
 @return CJGAVVideoRecorderOptions
 */
+ (instancetype)defaultOptions{
    
    CJGAVVideoRecorderOptions *options = [CJGAVVideoRecorderOptions defaultOptionsForSessionPreset: CJGAVCaptureSessionPreset_Default];
    return options;
}

/**
 视频配置(质量)
 
 @param sessionPreset 视频分辨率
 @return CJGAVVideoRecorderOptions
 */
+ (instancetype)defaultOptionsForSessionPreset:(CJGAVCaptureSessionPreset)sessionPreset{
    
    CJGAVVideoRecorderOptions *options = [CJGAVVideoRecorderOptions defaultOptionsForSessionPreset:sessionPreset videoRecordPosition:CJGAVVideoRecordPositionFront];
    return options;
}

/**
 视频配置(质量&是否是横屏)
 
 @param sessionPreset 视频分辨率
 @param videoRecordPosition 摄像机位置
 @return CJGAVVideoRecorderOptions
 */
+ (instancetype)defaultOptionsForSessionPreset:(CJGAVCaptureSessionPreset)sessionPreset videoRecordPosition:(CJGAVVideoRecordPosition)videoRecordPosition{
    
    CJGAVVideoRecorderOptions *options = [CJGAVVideoRecorderOptions new];
    options.sessionPreset = sessionPreset;
    options.recordPosition = videoRecordPosition;
    options.recordOutputType = CJGAVVideoRecordVideoDataOutput;
    options.isOutPreview = YES;
    options.outputFileName = @"VideoFile";
    options.saveSuffixFormat = @"mp4";

    switch (sessionPreset)
    {
        case  CJGAVCaptureSessionPreset_Low:
        {
            options.avSessionPreset = AVCaptureSessionPresetLow;
        }
            break;
        case  CJGAVCaptureSessionPreset_Medium:
        {
            options.avSessionPreset = AVCaptureSessionPresetMedium;
        }
            break;
        case  CJGAVCaptureSessionPreset_High:
        {
            options.avSessionPreset = AVCaptureSessionPresetHigh;
        }
            break;
        default:
            
            options.avSessionPreset = AVCaptureSessionPresetHigh;
            break;
    }
    switch (videoRecordPosition)
    {
        case  CJGAVVideoRecordPositionFront:
        {
            options.devicePosition = AVCaptureDevicePositionFront;
        }
            break;
        case  CJGAVVideoRecordPositionBack:
        {
            options.devicePosition = AVCaptureDevicePositionBack;
        }
            break;
        case  CJGAVVideoRecordPositionUnspecified:
        {
            options.devicePosition = AVCaptureDevicePositionUnspecified;
        }
            break;
        default:
            break;
    }
    return options;
}

/**
 设置默认参数配置(可以重置父类的默认参数，不设置的话，父类的默认参数会无效)
 */
- (void)setConfig;
{
    [super setConfig];
}
@end
