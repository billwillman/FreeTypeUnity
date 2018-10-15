//
//  EOCBook.h
//  dataStruct
//
//  Created by guoxiaodong on 14-8-7.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EOCPerson;

@interface EOCBook : NSObject
@property (nonatomic)NSString* bookName;
@property (nonatomic)NSString* bookPrice;
@property (nonatomic,weak)EOCPerson* p;//测试ARC的循环引用.

-(void) printfLog;
-(void) startPolling;
@end
