//
//  ViewController.h
//  dataStruct
//
//  Created by guoxiaodong on 14-7-28.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <UIKit/UIKit.h>
@class ScreenAxisView;


@interface ViewController : UIViewController
@property  (nonatomic)  ScreenAxisView* axis;
@property (nonatomic) UILabel* label;
-(void) printPoint:(NSArray*)array;
@end
