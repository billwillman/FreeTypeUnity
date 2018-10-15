//
//  AppDelegate.m
//  dataStruct
//
//  Created by guoxiaodong on 14-7-28.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "AppDelegate.h"
#include "myStack.h"

#import "ViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [[NSNotificationCenter  defaultCenter] addObserver:self selector:@selector(printPoint:) name:@"SDK_LOGIN_SUCCESSFUL" object:nil];
    _view = [[ViewController alloc] init];
    self.window.rootViewController = _view;
    [self.window makeKeyAndVisible];
    //测试循环引用
    {
        EOCPerson* person = [[EOCPerson alloc]init];
        [person textBlock];
    }
    {
        NSString *str = @"origin string";
        NSString *strCopy = [str copy];
        NSMutableString *mstrCopy = [str mutableCopy];
        [mstrCopy appendString:@"??"];
    }
    //测试nsstring的copy
    {
        NSMutableString *mstr = [NSMutableString stringWithString:@"origin"];
        NSString *strCopy = [mstr copy];
        NSMutableString *mstrCopy = [mstr copy];
        NSMutableString *mstrMCopy = [mstr mutableCopy];
        //[mstrCopy appendString:@"1111"];  //error
        [mstr appendString:@"222"];
        [mstrMCopy appendString:@"333"];
    }
    //测试字符串而翻转
    {
        //0.输出原始字符串
        char* str = "this is very good";printf("%s\n",str);
        char* reversal= (char*)calloc(1, 100);
        char* result= (char*)calloc(1, 100);
        int length=0;
        
        //1.翻转所有字符串
        reverString(str,strlen(str),reversal);
        printf("%s\n",reversal);
        
        //2.翻转单词
        char* index = reversal;
        char* reversalPtr = reversal;
        char* resultPtr = result;
        while (*index) {
            if (*index ==' ') {
                reverString(reversalPtr,length,resultPtr);
                reversalPtr= index+1 ;
                resultPtr += length;
                *(resultPtr++) = ' ';
                length = 0;
            }
            else {
                length++;
            }
            index ++;
        }
        
        //3.最后一个单词，翻转一下。
        reverString(reversalPtr,length,resultPtr);
        printf("%s\n",result);
        
        //4.清理数据
        free(reversal);
        reversalPtr=NULL;
        free(result);
        result=NULL;
    }
    return YES;
}
-(void) printPoint:(NSNotification*)notification{
    NSArray* array = notification.object;
    [_view printPoint:array];
}
void reverString(char* str,int length,char*buffer){
    if (length<=0) {
        return;
    }
    myStack * stack = initStack();
    int i=0;
    while (i<length) {
        push(stack,str);
        str++;
        i++;
    }
    //1.整体翻转过来
    char* tmp;
    while (tmp =(char*)pop(stack)) {
        *buffer = *tmp;
        buffer++;
    }
    freeStack(stack);
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
