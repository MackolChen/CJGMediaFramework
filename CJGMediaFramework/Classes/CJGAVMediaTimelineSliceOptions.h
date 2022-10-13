//
//  CJGAVMediaTimelineSliceOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMediaAssetOptions.h"
#import "CJGAVEncodeAudioSetting.h"

NS_ASSUME_NONNULL_BEGIN

/**
 CJGAVMediaTimelineSliceComposition
 将一个音视频的一个或多个多个片段进行（包括快慢速）编辑合成状态
 */
typedef NS_ENUM(NSInteger,CJGAVMediaTimelineSliceCompositionStatus)
{
    /**
     *  未知状态
     */
    CJGAVMediaTimelineSliceCompositionStatusUnknown,
    
    /**
     *  开始合成
     */
    CJGAVMediaTimelineSliceCompositionStatusStart,
    
    /**
     * 正在合成
     */
    CJGAVMediaTimelineSliceCompositionStatusComposing,
    
    /**
     * 操作完成
     */
    CJGAVMediaTimelineSliceCompositionStatusCompleted,
    
    /**
     * 保存失败
     */
    CJGAVMediaTimelineSliceCompositionStatusFailed,
    
    /**
     * 已取消
     */
    CJGAVMediaTimelineSliceCompositionStatusCancelled,
};

/**
 媒体资源音视频分段时间线（包括快慢速）编辑工具的配置项
 */
@interface CJGAVMediaTimelineSliceOptions :CJGAVMediaAssetOptions

// 状态
@property (nonatomic, readonly, assign) CJGAVMediaTimelineSliceCompositionStatus status;

/**
 导出音频编码设置项
 */
@property (nonatomic, strong) CJGAVEncodeAudioSetting *audioSetting;


@end


NS_ASSUME_NONNULL_END
