//
//  dyArray.h
//  dataStruct
//
//  Created by hherima on 14-7-28.
//  Copyright (c) 2014年 . All rights reserved.
//

#ifndef dataStruct_dyArray_h
#define dataStruct_dyArray_h
#include <stdlib.h>
#include "cpPlatform.h"


typedef void (*DataDestroyFunc)(void *);
typedef cp_bool (*DataCmpFunc)(void *,void *);
typedef void (*DataVisitFunc)(void *);


    
struct DynamicArray
{
    void **m_ppData; //the address of the allocated array.
    cp_int32 m_nAllocSize; //the allocated array size.
    cp_int32 m_nSize;  //the used size of the array.
    DataDestroyFunc m_fDestroy; //the callback function to destroy one data.
    DataCmpFunc     m_fCmp; //the callback function to compare one data.
    DataVisitFunc   m_fVisit; //the callback function to visit each data.
};
typedef struct DynamicArray DyArray;
    
    DyArray*   DyArrayCreate(DataDestroyFunc pDataDestroy);
    cp_bool    DyArrayInsert(DyArray* pArr, cp_int32 nIndex, void* pData);
    cp_bool    DyArrayPrepend(DyArray* pArr, void* pData);
    cp_bool    DyArrayAppend(DyArray* pArr, void* pData);
    cp_bool    DyArrayDelete(DyArray* pArr, cp_int32 nIndex);
    cp_bool    DyArrayDeleteEx(DyArray* pArr, cp_int32 nBegin,cp_int32 nEnd);
    cp_bool    DyArrayGetByIndex(DyArray* pArr, cp_int32 nIndex, void** ppData);
    cp_bool    DyArrayGetFirst(DyArray* pArr,void** ppData);
    cp_bool    DyArrayGetLast(DyArray* pArr,void** ppData);
    cp_bool    DyArraySetByIndex(DyArray* pArr, cp_int32 nIndex, void* pData);
    cp_int32   DyArrayLength(DyArray* pArr);
    cp_int32   DyArrayFind(DyArray* pArr, DataCmpFunc pCmp,void *pData);
    cp_bool    DyArrayForEach(DyArray* pArr, DataVisitFunc pVisit);
    void       DyArrayDestroy(DyArray* pArr);
    void       DyArrayDestroyCustom(DyArray* pArr,DataDestroyFunc pDataDestroy);
    void       DyArrayReset(DyArray* pArr);//shrink
    void       DyArrayClear(DyArray* pArr);//not shrink
    void       DyArrayResetCustom(DyArray* pArr,DataDestroyFunc pDataDestroy);
    void       DyArrayClearCustom(DyArray* pArr,DataDestroyFunc pDataDestroy);//not shrink

#endif
