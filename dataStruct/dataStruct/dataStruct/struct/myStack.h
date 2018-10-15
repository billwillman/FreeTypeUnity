//
//  myStack.h
//  dataStruct
//
//  Created by guoxiaodong on 14-8-12.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#ifndef dataStruct_myStack_h
#define dataStruct_myStack_h

#define kStacksize 100

typedef struct{
    void* entity[kStacksize];
    int top;
    }myStack;

myStack* initStack();
void push(myStack* s,void* p);
void* pop(myStack* s);
void freeStack(myStack* s);
#endif
