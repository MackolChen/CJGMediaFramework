//
//  CJGAVAudioRecorder_m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/28.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVAudioRecorderOptions.h"

@implementation CJGAVAudioRecorderOptions

+ (instancetype)defaultOptions{
    return [super defaultOptions];
}

#pragma mark --- setter getter
- (void)setRecordQuality:(CJGAVAudioRecordQuality)recordQuality{
    if(_recordQuality == recordQuality) return;
    _recordQuality = recordQuality;
    
    switch (recordQuality)
    {
        case  CJGAVAudioRecordQuality_min:
        {
            self.recordSampleRate = CJGAVAudioRecordSampleRate_16000Hz;
            self.recordBitRate = _audioSetting.audioChannels == 1 ? CJGAVAudioRecordBitRate_32Kbps : CJGAVAudioRecordBitRate_48Kbps;
            self.recordBitDepth = CJGAVAudioRecordBitDepth_8d;
        }
            break;
        case  CJGAVAudioRecordQuality_Low:
        {
            self.recordSampleRate = CJGAVAudioRecordSampleRate_22050Hz;
            self.recordBitRate = _audioSetting.audioChannels == 1 ? CJGAVAudioRecordBitRate_48Kbps : CJGAVAudioRecordBitRate_64Kbps;
            self.recordBitDepth = CJGAVAudioRecordBitDepth_16d;
        }
            break;
        case  CJGAVAudioRecordQuality_Medium:
        {
            self.recordSampleRate = CJGAVAudioRecordSampleRate_32000Hz;
            self.recordBitRate = _audioSetting.audioChannels == 1 ? CJGAVAudioRecordBitRate_64Kbps : CJGAVAudioRecordBitRate_96Kbps;
            self.recordBitDepth = CJGAVAudioRecordBitDepth_16d;
            
        }
            break;
        case  CJGAVAudioRecordQuality_High:
        {
            self.recordSampleRate = CJGAVAudioRecordSampleRate_44100Hz;
            self.recordBitRate = _audioSetting.audioChannels == 1 ? CJGAVAudioRecordBitRate_96Kbps : CJGAVAudioRecordBitRate_128Kbps;
            self.recordBitDepth = CJGAVAudioRecordBitDepth_16d;
            
        }
            break;
        case  CJGAVAudioRecordQuality_Max:
        {
            self.recordSampleRate = CJGAVAudioRecordSampleRate_48000Hz;
            self.recordBitRate = _audioSetting.audioChannels == 1 ? CJGAVAudioRecordBitRate_96Kbps : CJGAVAudioRecordBitRate_128Kbps;
            self.recordBitDepth = CJGAVAudioRecordBitDepth_24d;
        }
            break;
        default:
            self.recordSampleRate = CJGAVAudioRecordSampleRate_32000Hz;
            self.recordBitRate = _audioSetting.audioChannels == 1 ? CJGAVAudioRecordBitRate_64Kbps : CJGAVAudioRecordBitRate_96Kbps;
            self.recordBitDepth = CJGAVAudioRecordBitDepth_16d;
            break;
    }
}

- (void)setAudioChannels:(NSUInteger)audioChannels{
    if(_audioChannels == audioChannels) return;
    _audioChannels = audioChannels;
    self.audioSetting.audioChannels = _audioChannels;
}
- (NSUInteger)audioChannels{
    if (!_audioChannels) {
        
        _audioChannels = _audioChannels ? _audioChannels : 1;
    }
    return _audioChannels;
}

- (void)setRecordSampleRate:(CJGAVAudioRecordSampleRate)recordSampleRate{
    if(_recordSampleRate == recordSampleRate) return;
    _recordSampleRate = recordSampleRate;
    self.audioSetting.audioSampleRat = _recordSampleRate;
}

- (void)setRecordBitDepth:(CJGAVAudioRecordBitDepth)recordBitDepth{
    if(_recordBitDepth == recordBitDepth) return;
    _recordBitDepth = recordBitDepth;
    self.audioSetting.audioLinearBitDepth = _recordBitDepth;
}

- (void)setRecordBitRate:(CJGAVAudioRecordBitRate)recordBitRate{
    if(_recordBitRate == recordBitRate) return;
    _recordBitRate = recordBitRate;
    self.audioSetting.encoderBitRate = _recordBitRate;
}

- (CJGAVEncodeAudioSetting *)audioSetting{
    if (!_audioSetting) {
        _audioSetting = [CJGAVEncodeAudioSetting PCMAudioSetting];
    }
    return _audioSetting;
}

/**
 设置默认参数配置(可以重置父类的默认参数，不设置的话，父类的默认参数会无效)
 */
- (void)setConfig;
{
    [super setConfig];
    
    _isAcousticTimer = NO;

    //修改父类的默认项
    _meidaType = CJGAVMediaTypeAudio;
    _outputFileType = CJGAVAudioOutputFileTypeM4A;
    _outputFileName = @"audioRecordFile";
    _saveSuffixFormat = @"m4a";
    
    //设置该类的默认项
    self.audioChannels = 1;
    self.recordQuality = CJGAVAudioRecordQuality_Default;
}

@end
