//
//  CJGMediaAssetInfo.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/15.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVMediaInfo.h"
#import "CJGAVAudioInfo.h"
#import "CJGAVVideoInfo.h"

NS_ASSUME_NONNULL_BEGIN
/**
 媒体素材中的音视频信息
 */
typedef void(^lsqMovieInfoLoadCompletionHandler)(void);

@interface CJGMediaAssetInfo : CJGAVMediaInfo

/**
 根据 AVAsset 初始化 CJGMediaAssetInfo
 
 @param asset 资产信息
 @return CJGMediaAssetInfo
 */
- (instancetype)initWithAsset:(AVAsset *)asset;

/**
 视频轨道信息
 */
@property (nonatomic,readonly)AVAsset *asset;

/**
 视频轨道信息
 */
@property (nonatomic,readonly)CJGAVVideoInfo *videoInfo;

/**
 音频轨道信息
 */
@property (nonatomic,readonly)CJGAVAudioInfo *audioInfo;

/**
 异步加载视频信息
 
 @param asset AVAsset
 */
- (void)loadSynchronouslyForAssetInfo:(AVAsset *)asset;


@end

NS_ASSUME_NONNULL_END
