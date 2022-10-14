//
//  CJGAVSingleAudioPlayer.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/29.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVPlayCoreBase.h"

NS_ASSUME_NONNULL_BEGIN
@class CJGAVSingleAudioPlayer;
@protocol CJGAVSingleAudioPlayerDelegate <NSObject,CJGAVPlayCoreBaseDelegate>

/**
 播放器状态变化
 @param state 状态
 @param player 播放器
 */
- (void)didChangedAudioPlayState:(CJGAVPlayerState)state player:(CJGAVSingleAudioPlayer *)player;

@end
@interface CJGAVSingleAudioPlayer : CJGAVPlayCoreBase

@property (nonatomic,weak) id<CJGAVSingleAudioPlayerDelegate> delegate;

/**单例类的定时器只能自行销毁*/
+ (instancetype)player;

//播放音效
- (void)playSound;

//摧毁音效
- (void)disposeSound;

@end

NS_ASSUME_NONNULL_END
