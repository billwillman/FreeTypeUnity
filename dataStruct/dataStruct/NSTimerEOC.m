//
//  NSTimerEOC.m
//  dataStruct
//
//  Created by guoxiaodong on 14-8-10.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "NSTimerEOC.h"

@implementation NSTimer(EOCBlockSupport)
+(NSTimer*) eoc_scheduledTimerWithTimeInterval:(NSTimeInterval)interval block:(void(^)())block repeats:(BOOL)repeats{
    return [self scheduledTimerWithTimeInterval:interval target:self selector:@selector(eoc_blockInvoke:) userInfo:[block copy] repeats:repeats];
}
+(void)eoc_blockInvoke:(NSTimer*)timer{
    void(^block)() = timer.userInfo;
    if(block){
        block();
    }
}
@end
