//
//  CJGAVPlayerInterface.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/27.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CJGAVPlayerInterface;

@protocol CJGAVPlayerDelegate <NSObject>
@optional
/**
 播放器状态变化
 @param state 状态
 @param player 播放器
 */
- (void)CJGAVPlayerStateChange:(CJGAVPlayerState)state player:(id<CJGAVPlayerInterface>)player;

/**
 视频源开始加载后调用 ，返回视频的长度
 @param time 长度（秒）
 @param player 播放器
 */
- (void)CJGAVPlayerTotalTime:(CGFloat)time player:(id<CJGAVPlayerInterface>)player;

/**
 视频源加载时调用 ，返回视频的缓冲长度
 @param time 长度（秒）
 @param player 播放器
 */
- (void)CJGAVPlayerLoadTime:(CGFloat)time player:(id <CJGAVPlayerInterface>)player;

/**
 播放时调用，返回当前时间
 @param time 播放到当前的时间（秒）
 @param player 播放器
 */
- (void)CJGAVPlayerCurrentTime:(CGFloat)time player:(id <CJGAVPlayerInterface>)player;

@end

@protocol CJGAVPlayerInterface <NSObject>

@optional

/**
 音视频总时间长度
 */
@property (nonatomic, assign) NSTimeInterval timeInterval;


@end

NS_ASSUME_NONNULL_END
