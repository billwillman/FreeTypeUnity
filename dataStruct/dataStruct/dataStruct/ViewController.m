//
//  ViewController.m
//  dataStruct
//
//  Created by guoxiaodong on 14-7-28.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "ViewController.h"
#import "ScreenAxisView.h"
#import "picCompose.h"

struct data{
    unsigned int FieldA:8;
    unsigned int FieldB:4;
    unsigned int FieldC:2;
    unsigned int FieldD:1;
};
@interface ViewController()
{
    picCompose* _picTree;
    CGFloat width;
    CGFloat height;
    NSString* _currentMode;
}
@end
static NSString* const kLeftMode =     @"left";
static NSString* const kRightMode =    @"right";
static NSString* const kMiddleMode =   @"middle";
static NSString* const kLevelMode =   @"level";

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    //
    width = 320;
    height = 500;
    _currentMode = kRightMode;
    //
    _axis = [[ScreenAxisView alloc]initWithFrame:CGRectMake(0,22, 320, 500)];
    _axis.backgroundColor = [UIColor whiteColor];//设置透明
	// Do any additional setup after loading the view, typically from a nib.
    self.view = _axis;
    //
    UIButton *leftMode = [UIButton buttonWithType:UIButtonTypeCustom];
    leftMode.frame = CGRectMake(160,430,45, 28);
    [leftMode setTitle:@"left" forState:UIControlStateNormal];
    [leftMode setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [leftMode setBackgroundColor:[UIColor redColor]];
    [leftMode addTarget:self action:@selector(changeMode:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:leftMode];
    //
    UIButton *rightMode = [UIButton buttonWithType:UIButtonTypeCustom];
    rightMode.frame = CGRectMake(210,430,45, 28);
    [rightMode setTitle:@"right" forState:UIControlStateNormal];
    [rightMode setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [rightMode setBackgroundColor:[UIColor redColor]];
    [rightMode addTarget:self action:@selector(changeMode:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:rightMode];
    //
    UIButton *middleMode = [UIButton buttonWithType:UIButtonTypeCustom];
    middleMode.frame = CGRectMake(260,430,60, 28);
    [middleMode setTitle:@"level" forState:UIControlStateNormal];
    [middleMode setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [middleMode setBackgroundColor:[UIColor redColor]];
    [middleMode addTarget:self action:@selector(changeMode:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:middleMode];
    //显示当前的width
    _label = [[UILabel alloc] initWithFrame:CGRectMake(200,380, 120, 30)];
    [_label setBackgroundColor:[UIColor clearColor]];
    [_label setText:[NSString stringWithFormat:@"mode =%@ ",_currentMode]];
    [self.view addSubview:_label];
     //
    _picTree = [[picCompose alloc]initWithWidth:width Height:height];
    [_picTree createTree:PICCOMPOSE_right];
}

-(void) changeMode:(id)btn{
    UIButton* bt = btn;
    _currentMode = bt.titleLabel.text;
    [self selectMode:_currentMode];
    [_label setText:[NSString stringWithFormat:@"mode =%@ ",_currentMode]];
}
-(void) selectMode:(NSString*) mode{
    if ([kLeftMode isEqualToString:mode]) {
        [_picTree createTree:PICCOMPOSE_left];
    }
    else if (([kRightMode isEqualToString:mode])){
        [_picTree createTree:PICCOMPOSE_right];
    }
    else if (([kMiddleMode isEqualToString: mode])){
        [_picTree createTree:PICCOMPOSE_middle];
    }
    else if (([kLevelMode isEqualToString:mode])){
        [_picTree createTree:PICCOMPOSE_level];
    }
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
-(void) printPoint:(NSArray*)array{
    [_axis addRectArray:array];
}
@end
