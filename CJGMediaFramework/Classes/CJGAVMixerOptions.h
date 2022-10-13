//
//  CJGAVMixerOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/12.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMediaAssetOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 音频混合状态
 */
typedef NS_ENUM(NSInteger,CJGAVMixStatus)
{
    /**
     *  未知状态
     */
    CJGAVMixStatusUnknown,
    
    /**
     * 正在混合
     */
    CJGAVMixStatusMixing,
    
    /**
     * 操作完成
     */
    CJGAVMixStatusCompleted,
    
    /**
     * 操作失败
     */
    CJGAVMixStatusFailed,
    
    /**
     * 已取消
     */
    CJGAVMixStatusCancelled
    
};

@interface CJGAVMixerOptions : CJGAVMediaAssetOptions
{
    CJGAVMixStatus _mixStatus;
}

/**
 音视频混合状态
 */
@property (nonatomic, assign) CJGAVMixStatus mixStatus;

// 音轨是否可循环添加播放 默认 NO 不循环
@property (nonatomic, assign) BOOL enableCycleAdd;

@end

NS_ASSUME_NONNULL_END
