//
//  CJGAVOptions.h
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/26.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVOptions.h"

@implementation CJGAVOptions

/**
 默认配置/或直接init初始化一样
 
 @return CJGAVOptions
 */
+ (instancetype)defaultOptions;
{
    return [self.alloc init];
}

- (instancetype)init;
{
    self = [super init];
    if (self) {
        [self setConfig];
    }
    return self;
}

#pragma mark -- getter
- (CJGAVMediaOutputFileType)outputFileType{
    if (!_outputFileType) {
        
        switch (_meidaType) {
            case CJGAVMediaTypeAudio:
                _outputFileType = CJGAVAudioOutputFileTypeM4A;
                break;
            default:
                _outputFileType = CJGAVMediaOutputFileTypeM4V;
                break;
        }
    }
    return _outputFileType;
}

- (AVFileType)appOutputFileType{
    if (!_appOutputFileType) {
        
        switch (_outputFileType) {
            case CJGAVVideoOutputFileTypeQuickTimeMovie:
                _appOutputFileType = AVFileTypeQuickTimeMovie;
                break;
            case CJGAVVideoOutputFileTypeMPEG4:
                _appOutputFileType = AVFileTypeMPEG4;
                break;
            case CJGAVAudioOutputFileTypeM4A:
                _appOutputFileType = AVFileTypeAppleM4A;
                break;
            case CJGAVMediaOutputFileTypeM4V:
                _appOutputFileType = AVFileTypeAppleM4V;
                break;
            default:
                _appOutputFileType = AVFileTypeAppleM4V;
                break;
        }
    }
    return _appOutputFileType;
}

- (NSString *)saveSuffixFormat{
    
    if (!_saveSuffixFormat) {
        
        switch (self.outputFileType) {
            case CJGAVVideoOutputFileTypeQuickTimeMovie:
                _saveSuffixFormat = @"mov";
                break;
            case CJGAVVideoOutputFileTypeMPEG4:
                _saveSuffixFormat = @"mp4";
                break;
            case CJGAVAudioOutputFileTypeM4A:
                _saveSuffixFormat = @"m4a";
                break;
            case CJGAVMediaOutputFileTypeM4V:
                _saveSuffixFormat = @"m4v";
                break;
            default:
                _saveSuffixFormat = @"m4v";
                break;
        }
    }
    return _saveSuffixFormat;
}

- (NSURL *)outputFileURL{
    if (!_outputFileURL) {
        
        _outputFileURL = [NSURL fileURLWithPath:self.outputFilePath];
    }
    return _outputFileURL;
}

- (NSString *)outputFilePath{
    if (!_outputFilePath) {
        _outputFilePath = [self createSaveDatePath];
    }
    return _outputFilePath;
}

- (NSURL *)exportRandomFileURL{
    if (!_exportRandomFileURL) {
        
        _exportRandomFileURL = [NSURL fileURLWithPath:self.exportRandomFilePath];
    }
    return _exportRandomFileURL;
}

- (NSString *)exportRandomFilePath{
    if (!_exportRandomFilePath) {
        _exportRandomFilePath = [self exportSaveDatePath];
    }
    return _exportRandomFilePath;
}

/**
 创建数据操作的本地文件路径
 
 @return 文件保存的本地目录
 */
- (NSString *)createSaveDatePath;
{
//    [self clearCacheData];
    
    NSString *filePath = [CJGAVFileManager pathAppendDefaultDatePath:self.saveSuffixFormat];
    NSString *datePath = @"";
    
    switch (_sandboxDirType) {
            
        case CJGAVSandboxDirDocuments:
            datePath = [CJGAVFileManager pathInDocumentsWithDirPath:self.outputFileName filePath:filePath];
            break;
        case CJGAVSandboxDirLibrary:
            datePath = [CJGAVFileManager pathInLibraryWithDirPath:self.outputFileName filePath:filePath];
            break;
        case CJGAVSandboxDirCache:
            datePath = [CJGAVFileManager pathInCacheWithDirPath:self.outputFileName filePath:filePath];
            break;
        default:
            break;
    }
    if (_enableCreateFilePath) {//创建文件路径，其中的没有的文件夹也一并创建了
        
        [CJGAVFileManager createFilePath:datePath];
    }else{//只创建文件路径中的文件夹路径
        
        [CJGAVFileManager createDir:[CJGAVFileManager pathInCacheWithDirPath:self.outputFileName filePath:@""]];
    }

    return datePath;
}

/**
 导出创建的本地文件路径中的随机文件URLStr

 @return 文件URLStr
 */
- (NSString *)exportSaveDatePath;
{
    NSString *filePath = @"";
    
    switch (_sandboxDirType) {
            
        case CJGAVSandboxDirDocuments:
            filePath = [CJGAVFileManager filePathAtBasicPath:[CJGAVFileManager DocumentsPath] WithFileName:self.outputFileName];
            break;
        case CJGAVSandboxDirLibrary:
            filePath = [CJGAVFileManager filePathAtBasicPath:[CJGAVFileManager LibraryPath] WithFileName:self.outputFileName];
            break;
        case CJGAVSandboxDirCache:
            filePath = [CJGAVFileManager filePathAtBasicPath:[CJGAVFileManager CachePath] WithFileName:self.outputFileName];
            break;
        default:
            break;
    }
    return [CJGAVFileManager getRandomFilePathOnDirPath:filePath];;
}


/**
 清除当前路径文件
 */
- (BOOL)clearOutputFilePath;
{
    
    if (!_outputFilePath) return NO;
    
    [CJGAVFileManager deletePath:_outputFilePath];
    _outputFilePath = nil;
    _outputFileURL = nil;
    return YES;
}

/**
 清除缓存
 
 @return  返回清除缓存结果
 */
- (BOOL)clearCacheData;
{
    BOOL isClear = NO;
    
    //文件夹路径是否存在
    if ([CJGAVFileManager isExistDirAtPath:self.outputFileName]) return isClear;
    
    switch (_sandboxDirType) {
            
        case CJGAVSandboxDirDocuments:
            isClear = [CJGAVFileManager deleteCacheOnFilePath:[CJGAVFileManager filePathAtBasicPath:[CJGAVFileManager DocumentsPath] WithFileName:self.outputFileName]];
            break;
        case CJGAVSandboxDirLibrary:
            isClear = [CJGAVFileManager deleteCacheOnFilePath:[CJGAVFileManager filePathAtBasicPath:[CJGAVFileManager LibraryPath] WithFileName:self.outputFileName]];
            break;
        case CJGAVSandboxDirCache:
            isClear = [CJGAVFileManager deleteCacheOnFilePath:[CJGAVFileManager filePathAtBasicPath:[CJGAVFileManager CachePath] WithFileName:self.outputFileName]];
            break;
        default:
            break;
    }
    _outputFileURL = nil;
    _outputFilePath = nil;
    return isClear;
}

/**
 设置默认参数配置
 */
- (void)setConfig;
{
    
    _sandboxDirType = CJGAVSandboxDirCache;
    _enableCreateFilePath = YES;
    _outputFileName = @"CJGComponentTimeFile";
    _saveSuffixFormat = @"m4v";
}


@end
