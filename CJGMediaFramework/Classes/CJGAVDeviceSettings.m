//
//  AudioVideoDeviceSettings.m
//  AudioVideoSDK
//
//  Created by Jinguo Chen on 2022/6/6.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVDeviceSettings.h"

/**
 *  设备权限设置
 */
@interface CJGAVDeviceSettings()

@end

@implementation CJGAVDeviceSettings

#pragma mark - Camera

/**
 *  测试系统摄像头授权状态
 *
 *  @return    返回是否授权
 */
+ (BOOL)hasVideoAuthor;
{
    if ([self getSystemFloatVersion] < 7.0) return YES;
    
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    
    if(authStatus == AVAuthorizationStatusAuthorized || authStatus == AVAuthorizationStatusNotDetermined)return YES;
    
    return NO;
}
/**
 *  相机设备总数
 *
 *  @return 相机设备总数
 */
+ (int)getCameraCounts;
{
    
    int count = 0;
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *device in devices)
    {
        switch ([device position]) {
            case AVCaptureDevicePositionBack:
            case AVCaptureDevicePositionFront:
                count++;
                break;
            default:
                break;
        }
    }
    return count;
}

/**
 *  获取相机设备（前置或后置） 后置优先
 *
 *  @return 相机设备
 */
+ (AVCaptureDevice *)getBackOrFrontCamera;
{
    AVCaptureDevice *frontCamera = nil;
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *device in devices)
    {
        switch ([device position]) {
            case AVCaptureDevicePositionBack:
                return device;
            case AVCaptureDevicePositionFront:
                frontCamera = device;
                break;
            default:
                break;
        }
    }
    return frontCamera;
}

#pragma mark - Photo
/**
 *  是否用户已授权访问系统相册
 *
 *  @return 是否用户已授权访问系统相册
 */
+ (BOOL)hasAuthor;
{
    PHAuthorizationStatus status = [PHPhotoLibrary authorizationStatus];
    return status == PHAuthorizationStatusAuthorized;
}

/**
 *  是否未决定授权
 *
 *  @return 是否未决定授权
 */
+ (BOOL)notDetermined;
{
    PHAuthorizationStatus status = [PHPhotoLibrary authorizationStatus];
    return status == PHAuthorizationStatusNotDetermined;
}

/**
 *  测试系统相册授权状态
 *
 *  @param authorBlock 系统相册授权回调
 */
+ (void)testLibraryAuthor:(CJGAVSDKTSAssetsManagerAuthorBlock)authorBlock;
{
    if (!authorBlock) return;
    
    if ([self hasAuthor]){
        NSError *error = nil;
        authorBlock(error);
        return;
    };
    [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
        
        NSError *error = nil;
        
        if (status != PHAuthorizationStatusAuthorized) {
            NSInteger code = CJGAVAssetsAuthorizationErrorNotDetermined;
            switch (status) {
                case CJGAVAssetsAuthorizationErrorRestricted:
                    code = CJGAVAssetsAuthorizationErrorRestricted;
                    break;
                case PHAuthorizationStatusDenied:
                    code = CJGAVAssetsAuthorizationErrorDenied;
                    break;
                default:
                    break;
            }
            error = [NSError errorWithDomain:[NSString stringWithFormat:@"%@", [self class]]
                                        code:code userInfo:nil];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            authorBlock(error);
        });
    }];
}


#pragma mark - Microphone
/**
 *  是否用户已授权访问系统麦克风
 *
 *  @return 是否用户已授权访问系统麦克风
 */
+ (BOOL)haseMicrophoneAuthor;
{
    int version = [[[UIDevice currentDevice] systemVersion] intValue];
    BOOL isAuthorization = YES;
    if (version < 7.0) {
        isAuthorization = YES;
    }
    AVAuthorizationStatus videoAuthStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
    if (videoAuthStatus == AVAuthorizationStatusNotDetermined) {// 未询问用户是否授权
        AVAudioSession *audioSession = [AVAudioSession sharedInstance];
        //方式1:
        __block BOOL isAuthorizationWeak;
        [audioSession requestRecordPermission:^(BOOL granted) {
            isAuthorizationWeak = granted;
            if (granted) {
                
                NSLog(@"麦克风打开了");
            } else {
                
                NSLog(@"麦克风关闭了");
            }
        }];
        isAuthorization = isAuthorizationWeak;
        //方式2:
//        if ([audioSession respondsToSelector:@selector(requestRecordPermission:)]) {
//            [audioSession performSelector:@selector(requestRecordPermission:) withObject:^(BOOL granted) {
//                isAuthorization = granted;

//            }];
//        }
    } else if(videoAuthStatus == AVAuthorizationStatusRestricted || videoAuthStatus == AVAuthorizationStatusDenied) {
        // 未授权
        return NO;
    } else{
        // 已授权
        return YES;
    }
    return YES;
}

@end
