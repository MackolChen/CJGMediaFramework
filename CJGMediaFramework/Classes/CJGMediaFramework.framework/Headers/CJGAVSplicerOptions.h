//
//  CJGAVSpliceOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/8/15.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMediaAssetOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 CJGAVSpliceStatus 视频拼接状态
 */
typedef NS_ENUM(NSInteger,CJGAVSpliceStatus)
{
    /**
     *  未知状态
     */
   CJGAVSpliceStatusUnknown,
    
    /**
     * 正在合并
     */
   CJGAVSpliceStatusMerging,
    
    /**
     * 合并完成
     */
   CJGAVSpliceStatusCompleted,
    
    /**
     * 保存失败
     */
   CJGAVSpliceStatusFailed,
    
    /**
     * 已取消
     */
   CJGAVSpliceStatusCancelled
    
};

@interface CJGAVSplicerOptions : CJGAVMediaAssetOptions
{
    CJGAVSpliceStatus _spliceStatus;
}

// 状态
@property (nonatomic, assign) CJGAVSpliceStatus spliceStatus;

@end

NS_ASSUME_NONNULL_END
