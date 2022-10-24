//
//  CJGMediaAssetInfo.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/15.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGMediaAssetInfo.h"

@implementation CJGMediaAssetInfo

/**
 根据 AVAsset 初始化 CJGMediaAssetInfo
 
 @param asset 资产信息
 @return CJGMediaAssetInfo
 */
- (instancetype)initWithAsset:(AVAsset *)asset;
{
    if (self = [super init]) {
        
    }
    return self;
}

/**
 异步加载视频信息
 
 @param asset AVAsset
 */
- (void)loadSynchronouslyForAssetInfo:(AVAsset *)asset;
{
    
}
@end
