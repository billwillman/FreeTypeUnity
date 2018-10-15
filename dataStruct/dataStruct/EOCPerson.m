//
//  EOCPerson.m
//  dataStruct
//
//  Created by guoxiaodong on 14-8-7.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#import "EOCPerson.h"
//static int guo=0;
const NSTimeInterval kAnimationDuration = 0.3;
@implementation EOCPerson
@synthesize book = _book;

-(void)dealloc{
    NSLog(@"EOCPerson dealloc");
}
//
-(id)init{
    self  = [super init];
    _book = [[NSMutableArray alloc]init];

    return self;
}
-(void) textBlock
{
    int additional = 5;
    int(^addBlock)(int a ,int b) = ^(int a,int b){
        [self.book addObject:[[EOCBook alloc]init]];
        return additional;
    };
    __unused int add = addBlock(2,5);//add = 12
    //add = sizeof(*addBlock);
    
    [self testChar];
    
    /*
    void (^block)();
    if(1){
        block = ^{NSLog(@"Block A");};
    }else {
        block = ^{NSLog(@"Block B");};
    }
    block();
    */
}
-(void) printPerson{
    
    NSArray *anArray = @[@1,@2,@3,@4,@5];
    NSMutableArray *mArray = [NSMutableArray arrayWithArray:anArray];
    for (id object in [mArray reverseObjectEnumerator]) {
        NSLog(@"%@",object);
        [mArray removeObject:object];
    }
    
    NSArray *anNSArray = @[@1,@2,@3,@4,@5];
    CFArrayRef aCFArray = (__bridge CFArrayRef)anNSArray;
    NSLog(@"size of array =%li",CFArrayGetCount(aCFArray));
    

    NSLog(@"printPerson");
}
-(void) testChar{
    char* c = "i am good man";
//    c[-1];
    printf("char =%c\n",*(c+2));
}

@end
