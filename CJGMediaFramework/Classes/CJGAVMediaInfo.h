//
//  CJGAVMediaInfo.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/15.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVInfo.h"

NS_ASSUME_NONNULL_BEGIN



/**
 媒体音视频信息
 */
@interface CJGAVMediaInfo : CJGAVInfo
{
    CMTime _duration;
}

/**
 持续时间
 */
@property(nonatomic, readonly) CMTime duration;

/**
 异步加载音视频信息
 
 @param asset AVAsset
 @param handler 完成后回调
 */
-(void)loadAsynchronouslyForAssetInfo:(AVAsset *)asset completionHandler:(void (^)(void))handler;

/**
 同步加载音视频信息
 
 @param asset AVAsset
 */
-(void)loadSynchronouslyForAssetInfo:(AVAsset *)asset;

@end

NS_ASSUME_NONNULL_END
