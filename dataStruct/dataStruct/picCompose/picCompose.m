//
//  picCompose.m
//  dataStruct
//
//  Created by guoxiaodong on 14-8-12.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "picCompose.h"
#import "BTree.h"
@implementation picPrint
@end



@implementation picCompose

-(id)initWithWidth:(CGFloat)w Height:(CGFloat)h{
    self = [super init];
    maxLength = h;
    maxWidth = w;
    return self;
}

-(void)createTree:(PICCOMPOSE) mode{
    //1.清除原有的树.
    _root = nil;
    switch (mode) {
        case PICCOMPOSE_left:
            class_func = @selector(preTraveralTree:);
            break;
        case PICCOMPOSE_right:
            class_func = @selector(lastTraveralTree:);
            break;
        case PICCOMPOSE_middle:
            class_func = @selector(midTraveralTree:);
            break;
        case PICCOMPOSE_level:
            class_func = @selector(levelTraveralTree:);
            break;
        default:
            break;
    }
    
    //2.需要按照大小顺序
    NSMutableArray* tmp = [NSMutableArray array];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(120, 100) name:@"1.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(120, 100) name:@"2.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(100, 100) name:@"3.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(80, 21) name:@"4.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(70, 40) name:@"5.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(65, 30) name:@"6.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(50, 21) name:@"7.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(50, 21) name:@"8.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(50, 21) name:@"9.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(50, 21) name:@"10.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(40, 40) name:@"11.png"]];
    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(35, 30) name:@"12.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 35) name:@"13.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 15) name:@"14.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 25) name:@"15.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 15) name:@"16.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 15) name:@"17.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 15) name:@"18.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(35, 30) name:@"19.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(35, 30) name:@"20.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 40) name:@"21.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(35, 30) name:@"22.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 25) name:@"23.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 25) name:@"24.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 25) name:@"25.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 10) name:@"26.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 10) name:@"27.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 10) name:@"28.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 10) name:@"29.png"]];
//    [tmp addObject:[[picNode alloc]initWithSize:CGSizeMake(30, 5) name:@"30.png"]];
    
    //3.初始化根节点
    _root = [[BTreeNode alloc]init];
    _root.point = CGPointMake(0, 0);
    _root.virtualPic = [[picNode alloc]init];
    _root.virtualPic.size = CGSizeMake(maxWidth, maxLength);
    
    //4.将图片插入到tree中(为了最大限度利用资源，采用后序遍历的方法)
    for (id pic in tmp) {
        _currentPic = pic;
        if (class_func)
        {
            [self performSelector:class_func withObject:_root];
        }
    }
    //5.屏幕绘制坐标系
    NSMutableArray* a = [NSMutableArray array];
    [self preTraveralTree:_root array:a];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"SDK_LOGIN_SUCCESSFUL" object:a];
    
}
//遍历BTree，将所有元素装入数组
-(void) preTraveralTree:(BTreeNode*)node array:(NSMutableArray*)array{
    if (node ) {
        [self preTraveralTree:node.left array:array];
        if (node.isFull) {
            picPrint* pp = [[picPrint alloc]init];
            pp.rect = CGRectMake(node.point.x, node.point.y, node.virtualPic.size.width, node.virtualPic.size.height);
            pp.name = node.virtualPic.name;
            [array addObject:pp];
        }
        [self preTraveralTree:node.right array:array];
    }
}
//
-(bool) preTraveralTree:(BTreeNode*)node{
    if (node ) {
        bool ret ;
        ret = [self preTraveralTree:node.left];
        if (ret) {
            return YES;
        }
        //
        ret = [self insertPicture:node];
        if (ret) {
            return YES;
        }
        //
        ret = [self preTraveralTree:node.right];
        return ret;
    }
    return NO;
}

//
-(bool) midTraveralTree:(BTreeNode*)node{
    if (node) {
        bool ret = [self insertPicture:node];
        if (ret) {
            return YES;
        }
        ret = [self midTraveralTree:node.left];
        if (ret) {
            return YES;
        }
        ret = [self midTraveralTree:node.right];
        if (ret) {
            return YES;
        }
    }
    return NO;
}

//递归算法
-(bool) lastTraveralTree:(BTreeNode*)node{
    if (node ) {
        bool ret ;
        ret = [self lastTraveralTree:node.right];
        if (ret) {
            return YES;
        }
        //
        ret = [self insertPicture:node];
        if (ret) {
            return YES;
        }
        //
        ret = [self lastTraveralTree:node.left];
        return ret;
    }
    return NO;
}

//用栈实现
-(void) levelTraveralTree:(BTreeNode*)node{
    NSMutableArray* mArray = [NSMutableArray array];
    [mArray addObject:_root];
    while (mArray.count > 0) {
        BTreeNode* p = [mArray firstObject];
        [mArray removeObjectAtIndex:0];
        bool ret = [self insertPicture:p];
        if (ret) {
            return;
        }
        if (p.left) {
            [mArray addObject:p.left];
        }
        if (p.right) {
            [mArray addObject:p.right];
        }
    }
}

//放入图片。
-(bool) insertPicture:(BTreeNode*)node{
    
    //如果图片大小，可以放下这个rect。那么就设置一下这个rect的大小为图片大小，剩余面积分为left和right
    if (!node.isFull
        && node.virtualPic.size.width >= _currentPic.size.width
        && node.virtualPic.size.height >= _currentPic.size.height) {
        node.isFull = TRUE;
        /*
         拆分剩余rect为left和right两个分支。
         ●---------●-----------------
         | picture |   right        |
         |         |                |
         ●---------------------------
         |                          |
         |        left              |
         |                          |
         |                          |
         |                          |
         ----------------------------
         例如.picture已经占据了【左上角】区域。剩下的区域分为left和right。点（●）的地方就是CGPoint了。
         ● 优化点：如果picture是矩形，那么在生成left和right的时候。可以有两个选择：向下延伸，向右延伸。
         通常是向值小的一方延伸，这样保证值大的一方可以放进去更多的图片。
         ● 上面的例子是向右延伸。
         */
        node.left = [[BTreeNode alloc]init];
        node.left.point = CGPointMake(node.point.x, node.point.y + _currentPic.size.height);
        node.left.virtualPic = [[picNode alloc]init];
        
        node.right = [[BTreeNode alloc]init];
        node.right.point = CGPointMake(node.point.x+ _currentPic.size.width, node.point.y);
        node.right.virtualPic = [[picNode alloc]init];
        
        //优化一下
        if (_currentPic.size.width >= _currentPic.size.height)
        {
            //left的宽度是parent的宽度。高度是parent高度 - 图片的高度
            node.left.virtualPic.size = CGSizeMake(node.virtualPic.size.width, node.virtualPic.size.height - _currentPic.size.height);
            //right的宽度是，parent的宽度-图片的宽度。高度是图片的高度。
            node.right.virtualPic.size = CGSizeMake(node.virtualPic.size.width- _currentPic.size.width, _currentPic.size.height);
        }else{
            //left的宽度是图片的宽度。高度是parent高度 - 图片的高度（不变）
            node.left.virtualPic.size = CGSizeMake(_currentPic.size.width, node.virtualPic.size.height - _currentPic.size.height);
            //right的宽度是，parent的宽度-图片的宽度。高度parent的高度。
            node.right.virtualPic.size = CGSizeMake(node.virtualPic.size.width- _currentPic.size.width, node.virtualPic.size.height);
        }
        
        //将虚拟的pic复制
        node.virtualPic = [_currentPic copy];
    return YES;
    }
    return NO;
}


@end
