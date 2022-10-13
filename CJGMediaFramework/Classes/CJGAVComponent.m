//
//  CJGAVComponent.m
//  CJGAVComponent
//
//  Created by Jinguo Chen on 2022/6/21.
//  Copyright © 2019 ChenJinguo. All rights reserved.
//

#import "CJGAVComponent.h"

@implementation CJGAVComponent

/**
 *  设置日志输出级别
 *
 *  @param level 日志输出级别 (默认：CJGAVLogLevelFATAL 不输出)
 */
+ (void)setLogLevel:(CJGAVLogLevel)level;
{
    [CJGAVLog sharedLog].outputLevel = level;
}

@end
