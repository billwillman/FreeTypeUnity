//
//  picCompose.h
//  dataStruct
//
//  Created by guoxiaodong on 14-8-12.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <Foundation/Foundation.h>

@class picNode;
@class BTreeNode;
//用于打印出来
@interface picPrint : NSObject
@property (nonatomic) CGRect rect;
@property (nonatomic) NSString* name;
@end

typedef NS_ENUM(NSUInteger,PICCOMPOSE){
    PICCOMPOSE_left,
    PICCOMPOSE_right,
    PICCOMPOSE_middle,
    PICCOMPOSE_level,
};

@interface picCompose : NSObject
{
    BTreeNode*   _root;
    CGFloat maxLength ;
    CGFloat maxWidth  ;
    picNode*  _currentPic;
    SEL class_func ; //定义一个类方法指针class_func =
}
-(id)initWithWidth:(CGFloat)w Height:(CGFloat)h;
-(void)createTree:(PICCOMPOSE) mode;
@end
