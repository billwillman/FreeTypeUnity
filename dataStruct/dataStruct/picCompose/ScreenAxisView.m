//
//  ScreenAxisView.m
//  dataStruct
//
//  Created by guoxiaodong on 14-8-13.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "ScreenAxisView.h"
#import "picCompose.h"
#define kFontsize 8.0f

@interface ScreenAxisView ()
{
    NSArray* _points;
    UIFont* font;
}
@end
@implementation ScreenAxisView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:kFontsize];
    }
    return self;
}
-(void) addRectArray:(NSArray*)rects{
    _points = rects;
    [self setNeedsDisplay];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
 */
- (void)drawRect:(CGRect)rect
{
    rect.origin.y += 22;
    
    CGContextRef context = UIGraphicsGetCurrentContext(); //获取画布

    //CGContextSetRGBFillColor(context, 1.0, 0.0, 0.0, 1.0);  //设置矩形填充颜色：红色
    //CGContextFillRect(context, rect);                       //填充矩形
    CGContextSetRGBStrokeColor(context, 1.0, 0, 0, 1);        //设置画笔颜色：黑色
    CGContextSetLineWidth(context, 2.0);                    //设置画笔线条粗细
    CGContextAddRect(context,rect);                         //画矩形边框
    CGContextStrokePath(context);                              //执行绘画

    //CGContextDrawImage(context, imageRect, [image CGImage]);//这种方法图片被翻转了

    for (id p in _points) {
        picPrint* pp = p;
        CGRect r = pp.rect;
        r.origin.y+= rect.origin.y;
        CGContextSetRGBStrokeColor(context, 1.0, 0, 0, 1);      //设置画笔颜色：黑色
        CGContextSetLineWidth(context, 1.0);                    //设置画笔线条粗细
        CGContextAddRect(context,r);                            //画矩形边框
        CGContextStrokePath(context);                           //执行绘画
        //
        NSDictionary* d= @{NSForegroundColorAttributeName:[UIColor blueColor]
                           ,NSFontAttributeName:[UIFont systemFontOfSize:kFontsize]};
        NSString* s = [NSString stringWithFormat:@"[%.0f,%.0f]",r.origin.x,r.origin.y];
        //[s drawAtPoint:r.origin withAttributes:d];
        //
        [pp.name drawAtPoint:CGPointMake(r.origin.x+2, r.origin.y+r.size.height/2-kFontsize/2) withAttributes:d];
        //NSLog(@"%@",pp.name);
    }
}

@end

















