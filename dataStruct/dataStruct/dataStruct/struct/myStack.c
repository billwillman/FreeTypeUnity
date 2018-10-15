//
//  myStack.c
//  dataStruct
//
//  Created by guoxiaodong on 14-8-12.
//  Copyright (c) 2014年 chinasofti. All rights reserved.
//

#include <stdlib.h>
#include "myStack.h"

//
myStack* initStack(){
    myStack* s = (myStack*)malloc(sizeof(myStack));
    memset(s->entity,0,sizeof(kStacksize));
    s->top = -1;
    return s;
}
//
void push(myStack* s,void* p){
    if(s->top < kStacksize-1){
        s->entity[++s->top] = p;
    }
}
//
void* pop(myStack* s){
    if (s->top>=0 && s->top < kStacksize) {
        return s->entity[s->top--];
    }
    return NULL;
}
//
void freeStack(myStack* s){
    free(s);
}




