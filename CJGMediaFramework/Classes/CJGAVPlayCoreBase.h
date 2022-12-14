//
//  CJGAVPlayCoreBase.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVCoreBase.h"
#import "CJGProxy.h"

NS_ASSUME_NONNULL_BEGIN

/**
 播放状态
 */
typedef NS_ENUM(NSUInteger, CJGAVPlayerState) {
    CJGAVPlayerStateReadyToPlay, // 播放器准备完毕
    CJGAVPlayerStatePlaying, // 正在播放
    CJGAVPlayerStatePause, // 暂停
    CJGAVPlayerStateStop, // 停止播放
    CJGAVPlayerStateFinish, // 播放完毕
    CJGAVPlayerStateBuffering, // 缓冲中
    CJGAVPlayerStateBufferFinish, // 缓冲完成
    CJGAVPlayerStateFailed, // 播放器准备失败、网络原因，格式原因
    CJGAVPlayerStateUnKnow // 播放器准备失败，发生未知原因
};


/**
 播放类型
 */
typedef NS_ENUM(NSUInteger, CJGAVPlayerType) {
    CJGAVPlayerTypeAudio = 0, //音频播放
    CJGAVPlayerTypeVideo//视频播放
};

@protocol CJGAVPlayCoreBaseDelegate;
/**
 音视频播放的基础类
 */
@interface CJGAVPlayCoreBase : CJGAVCoreBase
{
    NSURL *_currentURL;//内部将_currentURLStr转为URL形式
    NSString *_currentURLStr;
    
    BOOL _isBuffering;
    BOOL _isAutomaticPlay;
    BOOL _isPlaying;
    CJGAVPlayerType _playerType;
    float _volume;
    
    NSTimer *_playTimer;//播放定时器
    NSTimeInterval _currentTimeLength;//当前播放时间
    NSTimeInterval _totalTimeLength;//总播放时间
    double _progressScale;//_currentTimeLength/_totalTimeLength,进度所占比例
}

/**
 当前播放器正在播放的urlstr
 */
@property (nonatomic, copy) NSString *currentURLStr;

/**
 是否在缓冲
 */
@property (nonatomic, assign) BOOL isBuffering;

/**
 是否开启自动播放,默认是YES
 */
@property (nonatomic, assign) BOOL isAutomaticPlay;

/**
 是否正在播放
 */
@property (nonatomic, assign, readonly) BOOL isPlaying;

/**
 播放类型
 */
@property (nonatomic, assign) CJGAVPlayerType playerType;

/**
 播放声音的音量
 */
@property (nonatomic, assign) float volume;

/**
 音视频当前播放时间长度
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentTimeLength;

/**
 音视频总时间长度
 */
@property (nonatomic, assign, readonly) NSTimeInterval totalTimeLength;

/**
 _currentTimeLength/_totalTimeLength, 音视频播放进度所占比例
 */
@property (nonatomic, assign, readonly) double progressScale;

@property (nonatomic, assign) AVAudioSessionCategory sessionCategory;

@property (nonatomic, weak) id<CJGAVPlayCoreBaseDelegate> delegate;

/**
 初始化创建播放源url的播放
 
 @param url 播放源
 @return 播放器
 */
- (instancetype)initWithURL:(NSString *)url;

/**
 激活Session控制当前的使用场景
 */
- (void)setAudioSession;

/**
 检索url是网络、本地哪一种
 
 @param url url
 @return 返回相应的url
 */
- (NSURL *)retrieveURL:(NSString *)url;

/**
 播放
 */
- (void)play;

/**
 暂停
 */
- (void)pause;

/**
 停止
 */
- (void)stop;


/**
 创建播放定时器
 */
- (void)addPlayTimer;

/**
 播放定时事件
 */
- (void)playTimeAction;


/**
 移除播放定时器
 */
- (void)removePlayTimer;


@end

@protocol CJGAVPlayCoreBaseDelegate <NSObject>


/**
 在录制音视频是添加定时器，定时事件回调
 
 @param currentTimeLength 录制的时间
 */
- (void)didChangedPlayCurrentTimeLength:(NSTimeInterval)currentTimeLength;

@end

NS_ASSUME_NONNULL_END
