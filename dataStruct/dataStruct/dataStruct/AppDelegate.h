//
//  AppDelegate.h
//  dataStruct
//
//  Created by guoxiaodong on 14-7-28.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EOCPerson.h"
#import "ViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    ViewController* _view;
}
@property (strong, nonatomic) UIWindow *window;
@property (nonatomic) EOCPerson *person;
@end
