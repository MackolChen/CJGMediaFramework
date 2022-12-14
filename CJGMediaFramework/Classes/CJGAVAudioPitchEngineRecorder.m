//
//  CJGAVAudioPitchEngineRecorder.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/7/18.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVAudioPitchEngineRecorder.h"
#import "CJGAVMediaSampleBufferAssistant.h"
#import "CJGAVMeidaTimelineSlice.h"

@interface  CJGAVAudioPitchEngineRecorder()
<
AVCaptureAudioDataOutputSampleBufferDelegate,
CJGAVAudioPitchEngineDelegate
>

{
    AVCaptureDeviceInput *_audioInput;
    AVCaptureAudioDataOutput *_audioOutput;
    AVCaptureSession *_captureSession;
    AVCaptureDevice *_microphone;
    
    AVAssetWriter *_audioWriter;
    AVAssetWriterInput *_audioWriterInput;
    
    dispatch_queue_t audioProcessingQueue;
    
    /** 纠正时间戳偏移量 */
    CMTime _offsetTime;
}


/**
 音频变调处理引擎
 */
@property (nonatomic, strong) CJGAVAudioPitchEngine *audioPitch;

/**
 当前正在录制的音频片段
 */
@property (nonatomic, strong) CJGAVMeidaTimelineSlice *recordingPitchTimeSlice;

/**
 记录全部录制片段
 */
@property (nonatomic, strong) NSMutableArray<CJGAVMeidaTimelineSlice *> *audioFragmentArray;

/**
 记录删除的录制片段
 */
@property (nonatomic, strong) NSMutableArray<CJGAVMeidaTimelineSlice *> *dropFragmentArr;


/**
 已录制的时长
 */
@property (nonatomic, assign, readonly) NSTimeInterval outputDuration;

@end

@implementation CJGAVAudioPitchEngineRecorder

#pragma mark -- init
- (instancetype)init
{
    self = [super init];
    if (self) {
        
        [self createCaptureSession];
    }
    return self;
}

- (instancetype)initWithAudioPitchEngineRecordOptions:(CJGAVAudioPitchEngineRecorderOptions *)pitchOptions;
{
    if (self = [super initWithAudioRecordOptions:pitchOptions]) {
        _pitchOptions = pitchOptions;
        [self createCaptureSession];
    }
    return self;
}

/**
 设置默认参数配置
 */
- (void)setConfig;
{
    [super setConfig];
    
    _audioFragmentArray = [NSMutableArray arrayWithCapacity:2];
    _dropFragmentArr = [NSMutableArray arrayWithCapacity:2];
    
    [self pitchOptions];
}

- (CJGAVAudioPitchEngineRecorderOptions *)pitchOptions{
    if (!_pitchOptions) {
        
        _pitchOptions = [[CJGAVAudioPitchEngineRecorderOptions alloc] init];
    }
    return _pitchOptions;
}

/**
 录音捕获会话初始化
 @return BOOL 是否初始化
 */
- (BOOL)createCaptureSession;
{
    if (_captureSession) return NO;
    
    _captureSession = [[AVCaptureSession alloc] init];
    
    //开始配置
    [_captureSession beginConfiguration];
    
    //麦克风设备
    _microphone = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
    //输入
    NSError *error;
    _audioInput = [[AVCaptureDeviceInput alloc] initWithDevice:_microphone error:&error];
    if (error) {
        CJGLError(@"audioInput init failed :%@",error);
        return NO;
    }
    //输出
    _audioOutput = [[AVCaptureAudioDataOutput alloc] init];
    
    if ([_captureSession canAddInput:_audioInput])
    {
        [_captureSession addInput:_audioInput];
    }else{
        CJGLError(@"Couldn't add audio audioInput");
        return NO;
    }
    if ([_captureSession canAddOutput:_audioOutput])
    {
        [_captureSession addOutput:_audioOutput];
    }else{
        CJGLError(@"Couldn't add audio audioOutput");
        return NO;
    }
    
    audioProcessingQueue = dispatch_get_global_queue(0, 0);
    [_audioOutput setSampleBufferDelegate:self queue:audioProcessingQueue];
    
    //结束配置
    [_captureSession commitConfiguration];
    
    return YES;
}


/**
 创建写入器
 */
- (void)startWriting{
    
    if (_audioWriter) {
        [_audioWriter cancelWriting];
        _audioWriter = nil;
    }
    
    NSError *error;
    //媒体数据写入器：用于将媒体数据写入指定的视听容器类型的新文件的对象。
    _audioWriter = [AVAssetWriter assetWriterWithURL:self.pitchOptions.outputFileURL fileType:AVFileTypeAppleM4A error:&error];
    if(error){
        CJGLError(@"audioWriter init failed :%@",error);
        return ;
    }
    
    // 媒体数据写入器：输入参数。媒体用于将媒体数据配置参数附加到资产写入器输出文件的单个跟踪中
    _audioWriterInput = [[AVAssetWriterInput alloc] initWithMediaType:AVMediaTypeAudio outputSettings:self.pitchOptions.audioSetting.audioConfigure];
    /**
     这里必须设置为no，否则录制结果播放不了，一个布尔值，指示输入是否应针对实时源调整其对媒体数据的处理。
     */
    _audioWriterInput.expectsMediaDataInRealTime = NO;
    
    //添加写入器输入
    if ([_audioWriter canAddInput:_audioWriterInput]) {
        [_audioWriter addInput:_audioWriterInput];
    }
    
    [_audioWriter startWriting];
    //这里开始时间是可以自己设置的
    [_audioWriter startSessionAtSourceTime:CMTimeMake(1, USEC_PER_SEC)];
}

- (void)cancelWriting{
    if (_audioWriter) {
        [_audioWriter cancelWriting];
        _audioWriter = nil;
    }
}

#pragma mark -- public methods
/**
 开始
 */
- (void)startRecord{
    
    if (!_captureSession) {
        
        [self createCaptureSession];
    }
    
    if (![_captureSession isRunning] && !_isPaused) {//开始录制
        
        _isRecording = YES;
        _isPaused = NO;

        //开始写数据
        [self startWriting];
        //开始捕获音频
        [_captureSession startRunning];
        //通知回调
        [self notifyRecordState:CJGAVRecordStateReadyToRecord];
    }
    
    if ([_captureSession isRunning] && _isPaused) {
        //继续录制
        [self resumeRecord];
    }
    
    //如果变调器存在，通过它可以刷新变调器的变调类型
    if (_audioPitch) {
        
        [self createAudioEnginePitch:nil];
    }
}

/**
 暂停
 */
- (void)pauseRecord{
    
    if(![_captureSession isRunning]) return;
    
    _isRecording = NO;
    _isPaused = YES;
    
    // 添加当前录制音频的时间切片数据
    [self appendRecordingAudioFrament];
}

/**
 停止
 */
- (void)stopRecord{
    
    if (![_captureSession isRunning]) return;

    if (!_isPaused) {//先暂停录制
        [self pauseRecord];
    }
    
    _isRecording = NO;
    _isPaused = NO;
    
    //停止捕获音频
    [_captureSession stopRunning];
    
    _offsetTime = kCMTimeInvalid;
    //入列缓存结束调用
    [_audioPitch processInputBufferEnd];
    
    //将所有未完成的输入标记为已完成，并完成输出文件的编写。
    [_audioWriter finishWritingWithCompletionHandler:^{
        if ( self.pitchOptions.outputFilePath) {
            [self startAudioComposition];
        }
        [self cancelWriting];
    }];
}

/**
 重录
 */
- (void)reRecording{
    
    _isRecording = NO;
    _isPaused = NO;
    
    //停止捕获音频数据
    if (_captureSession.isRunning) {
        [_captureSession stopRunning];
    }
    
    //直接取消写入器写入数据
    [self cancelWriting];
    
    //清除音频片段数组
    [self clearAudioFragmentArray];
    
    //删除临时存储文件
    [self.pitchOptions clearOutputFilePath];
}

/**
 取消录制
 */
- (void)cancelRecord;
{
    [self destory];
    
    //通知回调
    [self notifyRecordState:CJGAVRecordStateCanceled];
}

/**
 删除最后一个音频片段
 */
- (void)deleteLastAudioFragment;
{
    if (_audioFragmentArray.count == 0 || _isRecording) return;
    
    CJGAVMeidaTimelineSlice *lastFragment = [self getLastValidSpeedAudioFragment];
    if (lastFragment) {
        lastFragment.isRemove = YES;
        [_dropFragmentArr addObject:lastFragment];
    }
}

#pragma mark -- private methods
/**
 继续录制
 */
- (void)resumeRecord;
{
    if (![_captureSession isRunning] || !_isPaused) return;
    _isRecording = YES;
    _isPaused = NO;
    
    //继续录制
    //[self createAudioEnginePitch:nil];
    
    //通知回调
    [self notifyRecordState:CJGAVRecordStateResume];
}

/**
 合并视频
 */
- (void)startAudioComposition;
{
    if (!_dropFragmentArr.count) {
        
        //状态回调通知
        [self notifyRecordState:CJGAVRecordStateCompleted];
        //录制结果通知回调
        [self notifyRecordResult:_pitchOptions isOutputFilePath:YES isOutputDuration:YES];
        //清除数组
        [self clearAudioFragmentArray];
        return;
    }
    
    CJGAVMediaTimelineSliceOptions *timeSliceOptions = [[CJGAVMediaTimelineSliceOptions alloc] init];
    timeSliceOptions.mediaPath = _pitchOptions.outputFilePath;
    timeSliceOptions.audioSetting = _pitchOptions.audioSetting;
    
    CJGAVMediaTimelineSliceComposition *audioComposition = [[CJGAVMediaTimelineSliceComposition alloc] init];
    audioComposition.timeSliceOptions = timeSliceOptions;
    audioComposition.meidaFragmentArr = _audioFragmentArray;
    
    [audioComposition startAudioCompositionWithCompletionHandler:^(NSString * _Nonnull outputFilePath,NSTimeInterval mediaTotalTime, CJGAVMediaTimelineSliceCompositionStatus status) {
        switch (status)
        {
            case CJGAVMediaTimelineSliceCompositionStatusCompleted:
                //通知回调
                [self notifyRecordState:CJGAVRecordStateCompleted];
                //替换成合成的输出地址
                self.pitchOptions.outputFilePath = outputFilePath;
                self.pitchOptions.outputFileURL = [NSURL fileURLWithPath:outputFilePath];
                //音频处理之后的最终总时长
                self.pitchOptions.outputDuration = mediaTotalTime;
                [self notifyRecordResult:self.pitchOptions isOutputFilePath:YES isOutputDuration:YES];

                break;
            case CJGAVMediaTimelineSliceCompositionStatusFailed:
                
                //通知回调
                [self notifyRecordState:CJGAVRecordStateFailed];
                break;
            default:
                break;
        }
        
        //清除数组
        [self clearAudioFragmentArray];
    }];
}

/**
 已录制输出时长，不包含已删除的片段
 
 @return 有效输出时长
 */
- (NSTimeInterval)outputDuration;
{
    float recordingDuration = _isRecording ? CMTimeGetSeconds([self recordingPitchTimeSlicDurationTime]) : 0;
    float recordedDuration = _audioFragmentArray.count ? CMTimeGetSeconds([self getLastAudioFragmentDuration]) - CMTimeGetSeconds([self getAllRemoveAudioFragmentDuration]) : 0;
    
    //更新已录制的有效输出时长
    _pitchOptions.outputDuration = recordingDuration + recordedDuration;
    
    return recordingDuration + recordedDuration;
}


/**
 将当期录制的音频片段添加到数组
 */
- (void)appendRecordingAudioFrament;
{
    if(!_recordingPitchTimeSlice) return;
    [_audioFragmentArray addObject:_recordingPitchTimeSlice];
    _recordingPitchTimeSlice = nil;
}

/**
 计算录制过程中与开始时间获取持续时间
 @return CMTime
 */
- (CMTime)recordingPitchTimeSlicDurationTime;
{
    if (!_recordingPitchTimeSlice) return kCMTimeZero;
    return _recordingPitchTimeSlice.adjustedTime;
}

/**
 已录制片段的总时长 单位：/s:最后一次录制的结束时间
 @return Float64
 */
- (CMTime)getLastAudioFragmentDuration;
{
    if (_audioFragmentArray.count == 0) return kCMTimeZero;
   
    CJGAVMeidaTimelineSlice *pitchTimeSlice = _audioFragmentArray.lastObject;
    CMTime totalTime = pitchTimeSlice.end;
    return totalTime;
}

/**
 所有的已删除的片段持续时间 单位：/s
 @return Float64
 */
- (CMTime)getAllRemoveAudioFragmentDuration;
{
    CMTime totalTime = kCMTimeZero;
    for (CJGAVMeidaTimelineSlice *fragment in _dropFragmentArr) {
        totalTime = CMTimeAdd(totalTime, fragment.adjustedTime);
    }
    return totalTime;
}

/**
 获取最后一个录制片段
 @return CJGAVMeidaTimelineSlice
 */
- (CJGAVMeidaTimelineSlice *)getLastValidSpeedAudioFragment;
{
    if(_audioFragmentArray.count == 0) return nil;
    
    NSMutableArray<CJGAVMeidaTimelineSlice *> *allTimeRangeArray = [NSMutableArray arrayWithArray:_audioFragmentArray];
    [allTimeRangeArray removeObjectsInArray:_dropFragmentArr];
    CJGAVMeidaTimelineSlice *fragment = [allTimeRangeArray lastObject];
    return fragment;
}

/**
 移除录制声音配置
 */
- (void)removeInputsAndOutputs;
{
    [_captureSession beginConfiguration];
    if (_microphone != nil)
    {
        [_captureSession removeInput:_audioInput];
        [_captureSession removeOutput:_audioOutput];
        _audioInput = nil;
        _audioOutput = nil;
        _microphone = nil;
    }
    [_captureSession commitConfiguration];
    
    _captureSession = nil;
}

/**
 清除音频片段数组
 */
- (void)clearAudioFragmentArray;
{
    [_audioFragmentArray removeAllObjects];
    [_dropFragmentArr removeAllObjects];
}

#pragma mark - AVCaptureAudioDataOutputSampleBufferDelegate
- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    if (!_captureSession.isRunning) return;
    
    
    if(output == _audioOutput){
        
        if (!_audioPitch) {
            //创建音频变调引擎
            [self createAudioEnginePitch:sampleBuffer];
        }
        //将buffer数据喂给音频音调引擎
        [self processSampleBuffer:sampleBuffer];
    }
}


#pragma mark  ------------------------------------ CJGAVAudioPitchEngine 核心 API BEGIN ------------------------------------
/**
 step1: 创建音频变调 API
 */
- (void)createAudioEnginePitch:(CMSampleBufferRef)sampleBuffer;
{
    if (_audioPitch) {
        //重置引擎
        [_audioPitch reset];
        //刷新引擎数据
        [_audioPitch flush];
    }else{
        
        //通过buffer获取音频数据描述信息
        CMFormatDescriptionRef formatRef = CMSampleBufferGetFormatDescription(sampleBuffer);
        /** 获取 CMSampleBufferRef 音频信息 */
        CJGAVAudioTrackInfo *trackInfo = [[CJGAVAudioTrackInfo alloc] initWithCMAudioFormatDescriptionRef:formatRef];
        // 创建 CJGAVAudioPitchEngine 引擎
        // step1: 创建变声 API
        _audioPitch = [[CJGAVAudioPitchEngine alloc] initWithInputAudioInfo:trackInfo];
        _audioPitch.delegate = self;
    }
    
    [self processPitchOrSpeed];
}


/**
 step2:处理变调或变速
 */
- (void)processPitchOrSpeed{

    /**
     speed与speedMode只能使一个有效
     pitch与pitchType只能使一个有效
     */
    if (_pitchOptions.isSetPitch) {
        
        _audioPitch.pitch = _pitchOptions.pitch;
    }else if (_pitchOptions.isSetPitchType){
        
        _audioPitch.pitchType = _pitchOptions.pitchType;
    }else if (_pitchOptions.isSetSpeed){
        
        _audioPitch.speed = _pitchOptions.speed;
    }else if (_pitchOptions.isSetSpeedMode){
        
        _audioPitch.speedMode = _pitchOptions.speedMode;
    }else{
        
        _audioPitch.pitchType = CJGAVSoundPitchNormal;
    }
}

/**
 step3: 将数据送入 CJGAVAudioPitchEngine
 @param sampleBuffer CMSampleBufferRef
 */
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer;
{
    //最大时长是否设置
    if (_pitchOptions.maxRecordDelay != -1) {
        //已经录制的总时长是否大于最大允许的录制时长
        if (self.outputDuration >= _pitchOptions.maxRecordDelay) {
            //修正录制时长偏差
            _pitchOptions.outputDuration = _pitchOptions.maxRecordDelay;
            [self stopRecord];
        }
        return;
    }

    if (_isPaused) {//暂停
        _isRecording = NO;
        //录制状态通知回调
        [self notifyRecordState:CJGAVRecordStatePause];
        return;
    }
    
    _isRecording = YES;
    //录制状态通知回调
    [self notifyRecordState:CJGAVRecordStateRecording];

    /** 记录录制的时间片段 */
    if (!_recordingPitchTimeSlice) {
        _recordingPitchTimeSlice = [[CJGAVMeidaTimelineSlice alloc] init];
        
        //获取最后时间片段的结束时间
        CMTime lastEndTime = [self getLastAudioFragmentDuration];
        //当前正在录制的音频片段的时间赋值:lastEndTime上一次的录制结束时间，这一次录制的开始时间
        _recordingPitchTimeSlice.start = lastEndTime;
        
        //当前buffer显示（z录制）时间
        CMTime sampleBufferTime = CMSampleBufferGetOutputPresentationTimeStamp(sampleBuffer);
        //时间的偏移量,新老两次时间的间隔
        _offsetTime = CMTimeSubtract(sampleBufferTime, lastEndTime);
     }

    /**  调整 CMSampleBufferRef 写入时间 */
    CMSampleBufferRef tempSampleBuffer = [CJGAVMediaSampleBufferAssistant adjustPTS:sampleBuffer byOffset:_offsetTime];
    //深拷贝sampleBuffer
    CMSampleBufferRef copyBuffer = [CJGAVMediaSampleBufferAssistant sampleBufferCreateCopyWithDeep:tempSampleBuffer];
    CMSampleBufferInvalidate(tempSampleBuffer);
    CFRelease(tempSampleBuffer);
    tempSampleBuffer = NULL;
    
    // 获取处理后buffer的时间
    CMTime currentSampleTime = CMSampleBufferGetOutputPresentationTimeStamp(copyBuffer);
    
    //更新时间切片结束时间
    _recordingPitchTimeSlice.end = currentSampleTime;
    //更新输出时间
    _pitchOptions.outputDuration = self.outputDuration;
    //目的将输出时间回调出去
    [self notifyRecordResult:_pitchOptions isOutputFilePath:NO isOutputDuration:YES];
    
    // 将音频数据送入处理引擎处理
    [_audioPitch processInputBuffer:copyBuffer];
}

#pragma mark CJGAVAudioPitchEngineDelegate

/**
 step4: 接收 CJGAVAudioPitchEngine 处理后的数据
 @param pitchEngine 音频处理对象
 @param outputBuffer 变调变速后的音频数据
 @param autoRelease 是否释放音频数据，默认为NO
 */
- (void)pitchEngine:(CJGAVAudioPitchEngine *)pitchEngine syncAudioPitchOutputBuffer:(CMSampleBufferRef)outputBuffer autoRelease:(BOOL *)autoRelease;
{
    if (outputBuffer ) {
        
        if (_audioWriter.status == AVAssetWriterStatusWriting) {
            CMTime currentSampleTime = CMSampleBufferGetOutputPresentationTimeStamp(outputBuffer);
            //一个布尔值，指示输入是否准备好接受更多的媒体数据。
            while (!_audioWriterInput.readyForMoreMediaData) {
                //创建并返回一个日期对象，该对象设置为当前日期和时间的给定秒数。
                NSDate *maxDate = [NSDate dateWithTimeIntervalSinceNow:0.5];
                //运行循环，直到指定的日期，在此期间，它处理来自所有附加输入源的数据。
                [[NSRunLoop currentRunLoop] runUntilDate:maxDate];
            }
            if (!_audioWriterInput.readyForMoreMediaData)
            {
                
                CJGLDebug(@"2: Had to drop an audio frame %@", CFBridgingRelease(CMTimeCopyDescription(kCFAllocatorDefault, currentSampleTime)));
            }else{
                
                if (CMSampleBufferIsValid(outputBuffer) && outputBuffer != NULL) {
                    
                    //拼接buffer数据
                    if (![_audioWriterInput appendSampleBuffer:outputBuffer])
                        CJGLDebug(@"Problem appending audio buffer at time: %@", CFBridgingRelease(CMTimeCopyDescription(kCFAllocatorDefault, currentSampleTime)));
                }else{
                    
                    [_audioWriterInput markAsFinished];
                }
            }
        }
    }
    
    // 标识 syncAudioPitchOutputBuffer 回调处理完成后  CJGAVAudioPitchEngine 是否自动回收 outputBuffer
    // 如果后续需要对 outputBuffer 异步处理，可以将 autoRelease 设为 NO,或对 outputBuffer 进行 deep copy，防止 syncAudioPitchOutputBuffer 处理完成后被回收。
    *autoRelease = YES;
}
#pragma mark  ------------------------------------ CJGAVAudioPitchEngine 核心 API END ------------------------------------

/**
 录制状态：代理通知回调
 
 @param state 音频录制状态
 */
- (void)notifyRecordState:(CJGAVRecordState)state{
    
    if (_pitchOptions.recordStatus == state) return;
    _pitchOptions.recordStatus = state;
    
    // 状态回调
    if ([self.delegate respondsToSelector:@selector(didRecordingStatusChanged:recorder:)])
        [self.delegate didRecordingStatusChanged:state recorder:self];
}

/**
 录制结果：代理通知回调

 @param recoderOptions 音频的配置项结果
 */
- (void)notifyRecordResult:(CJGAVAudioRecorderOptions *)recoderOptions isOutputFilePath:(BOOL)isOutputFilePath isOutputDuration:(BOOL)isOutputDuration{
    
    //音频的全部结果回调
    if ([self.delegate respondsToSelector:@selector(didRecordedAudioResult:recorder:)])
        [self.delegate didRecordedAudioResult:recoderOptions recorder:self];
    
    if (isOutputDuration) {
        
        //已录制时间回调
        if ([self.delegate respondsToSelector:@selector(didCompletedOutputDuration:recorder:)])
            [self.delegate didCompletedOutputDuration:recoderOptions.outputDuration recorder:self];
    }
    
    if (isOutputFilePath) {
        
        //录制结果音频存储地址回调
        if ([self.delegate respondsToSelector:@selector(didCompletedOutputFilePath:recorder:)])
            [self.delegate didCompletedOutputFilePath:recoderOptions.outputFilePath recorder:self];
    }
}

/**
 摧毁音频音调引擎
 */
- (void)destory{
    [super destory];
    
    //停止捕获音频数据
    [_captureSession stopRunning];
    //清除音频捕获
    [self removeInputsAndOutputs];

    //销毁音频变调器
    if (_audioPitch) {
        [_audioPitch destory];
        _audioPitch = nil;
    }
    
    //删除临时存储文件
    [_pitchOptions clearOutputFilePath];
    
    //清除音频片段数组
    [self clearAudioFragmentArray];
}

@end
