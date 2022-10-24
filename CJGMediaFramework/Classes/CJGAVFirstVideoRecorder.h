//
//  VideoFirstRecorder.h
//  AudioVideoSDK
//
//  Created by Jinguo Chen on 2022/6/14.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVRecordVideoCoreBase.h"

NS_ASSUME_NONNULL_BEGIN

/**
 视频第一选择录制器
 */

@interface CJGAVFirstVideoRecorder : CJGAVRecordVideoCoreBase<CJGAVVideoRecorderInterface>
{
    CJGAVVideoRecorderOptions *_options;
}

/**
 视频配置项
 */
@property (nonatomic, strong , readonly) CJGAVVideoRecorderOptions *options;

/**
 代理
 */
@property (nonatomic, weak) id<CJGAVVideoRecorderDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
