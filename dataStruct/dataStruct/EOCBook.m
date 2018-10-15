//
//  EOCBook.m
//  dataStruct
//
//  Created by guoxiaodong on 14-8-7.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "EOCBook.h"
#import "NSTimerEOC.h"
#import "EOCPerson.h"
//static int guo=0;
static const NSTimeInterval kAnimationDuration = 0.3;
typedef void(^blk_t) (void) ;
@implementation EOCBook
{
    NSTimer* _pollTimer;
    blk_t blk;
}
-(id)init{
    self = [super init];
    blk = ^{NSLog(@"@self =%@",self);};
    [self startPolling];
    return self;
}
-(void)dealloc{
    NSLog(@"EOCBook dealloc");
}

-(void) printfLog{
    NSLog(@"printfLog EOCBook");
    
}
-(void) startPolling{
    __weak typeof(self) weakSelf = self;
    //_pollTimer = [NSTimer scheduledTimerWithTimeInterval:5.0 target:weakSelf selector:@selector(p_doPoll) userInfo:nil repeats:YES];
    _pollTimer = [NSTimer eoc_scheduledTimerWithTimeInterval:5.0 block:^{[weakSelf p_doPoll];}  repeats:YES];
}
-(void) p_doPoll{
    //poll the resource;
}
@end