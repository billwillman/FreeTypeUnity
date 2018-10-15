//
//  NSTimerEOC.h
//  dataStruct
//
//  Created by guoxiaodong on 14-8-10.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSTimer(EOCBlockSupport)

+(NSTimer*) eoc_scheduledTimerWithTimeInterval:(NSTimeInterval)interval block:(void(^)())block repeats:(BOOL)repeats;


@end
