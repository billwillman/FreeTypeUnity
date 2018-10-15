//
//  BTree.h
//  dataStruct
//
//  Created by guoxiaodong on 14-8-14.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface picNode: NSObject
@property (nonatomic) CGSize        size;
@property (nonatomic) NSString*     name;
-(id)initWithSize:(CGSize)size name:(NSString*)name;
@end



@interface BTreeNode: NSObject
@property  (nonatomic)  CGPoint         point;
@property  (nonatomic)  picNode*        virtualPic;
@property  (nonatomic)  bool            isRoute;
@property  (nonatomic)  bool            isFull;
@property  (nonatomic)  BTreeNode*    left;
@property  (nonatomic)  BTreeNode*    right;

@end
