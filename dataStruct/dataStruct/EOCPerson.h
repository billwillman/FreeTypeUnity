//
//  EOCPerson.h
//  dataStruct
//
//  Created by guoxiaodong on 14-8-7.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EOCBook.h"

@interface EOCPerson : NSObject
{
    NSMutableArray*   _book;
}
@property (nonatomic) NSString* firstName;
@property (nonatomic) NSString* lastName;
@property (nonatomic,strong) NSMutableArray* book;

-(void) textBlock;
-(void) printPerson;
@end
