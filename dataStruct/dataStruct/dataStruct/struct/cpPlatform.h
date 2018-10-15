//
//  cpPlatform.h
//  dataStruct
//
//  Created by hherima on 14-7-29.
//  Copyright (c) 2014年 . All rights reserved.
//

#ifndef dataStruct_cpPlatform_h
#define dataStruct_cpPlatform_h



enum
{
    CP_FALSE  =   0,
    CP_TRUE    =  !CP_FALSE
};


#define  F_MALLOC_TYPE(s) (s*)f_malloc(sizeof(s))
#define  FREEFUN free
#define  MIN_PRE_ALLOCATE_SIZE 10  //The initial size of the dynamic array.
#define  MEMSETFUN      memset
#define  REALLOCFUN     realloc
#define  MALLOCFUN      malloc
#define  MEMCMPFUN      memcmp
#define  MEMCPYFUN      memcpy



typedef unsigned char cp_bool;
typedef signed int cp_int32;
typedef char cp_int8;
typedef unsigned int cp_uint32;


#endif
