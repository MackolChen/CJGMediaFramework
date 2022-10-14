//
//  CJGAVCliperOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/14.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMediaAssetOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 音视频裁剪状态
 */
typedef NS_ENUM(NSInteger,CJGAVClipStatus)
{
    /**
     *  未知状态
     */
    CJGAVClipStatusUnknown,
    
    /**
     * 正在裁剪
     */
    CJGAVClipStatusClipping,
    
    /**
     * 裁剪完成
     */
    CJGAVClipStatusCompleted,
    
    /**
     * 保存失败
     */
    CJGAVClipStatusFailed,
    
    /**
     * 已取消
     */
    CJGAVClipStatusCancelled
};

@interface CJGAVClipperOptions : CJGAVMediaAssetOptions
{
    CJGAVClipStatus _clipStatus;
}

// 状态
@property (nonatomic, assign) CJGAVClipStatus clipStatus;

@end

NS_ASSUME_NONNULL_END
