//
//  BTree.m
//  dataStruct
//
//  Created by guoxiaodong on 14-8-14.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "BTree.h"

@implementation picNode
-(id)initWithSize:(CGSize)size name:(NSString*)name
{
    self = [super init];
    _size = size;
    _name = name;
    return self;
}
- (id)copyWithZone:(NSZone *)zone
{
    return self;
}
-(NSString*) description{
    return [NSString stringWithFormat:@"rect(%.0f,%.0f),name=%@",self.size.width,self.size.height,self.name];
}
@end

@implementation BTreeNode
-(NSString*) description{
    return [NSString stringWithFormat:@"point(%.0f,%.0f),isfull=%d,%@",self.point.x,self.point.y,self.isFull,self.virtualPic];
}
@end

