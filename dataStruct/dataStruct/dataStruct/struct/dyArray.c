//
//  dyArray.c
//  dataStruct
//
//  Created by hherima on 14-7-28.
//  Copyright (c) 2014年 . All rights reserved.
//


#include "dyArray.h"

void* f_malloc(cp_int32 size)
{
	void* p = MALLOCFUN(size);
	if(p)
		MEMSETFUN(p, 0, size);
    
	return p;
}
/**************************************************************************************************
【函数名】: DyArrayCreate
【描述】: 创建长度为MIN_PRE_ALLOCATE_SIZE的动态指针数组
【参数】:
 pDataDestroy: the callback function to destroy one data in data array.
【返回值】: 动态指针数组的地址
 ***************************************************************************************************/

DyArray* DyArrayCreate(DataDestroyFunc pDataDestroy)
{
	DyArray *pArr = NULL;
	pArr = F_MALLOC_TYPE(DyArray);
    
    //if the input parameter is invalid, return.
	if(!pArr)
    {
        return NULL;
    }
    //malloc memory for dynamic array and iniatilize it.
	pArr->m_fDestroy = pDataDestroy;
	pArr->m_ppData = (void *)f_malloc(sizeof(void *)*MIN_PRE_ALLOCATE_SIZE);
	if(!pArr->m_ppData)
	{
		FREEFUN(pArr);
		return NULL;
	}
	pArr->m_nAllocSize = MIN_PRE_ALLOCATE_SIZE;
	return pArr;
}

/**************************************************************************************************
【函数名】: DyArrayGetByIndex
【描述】:获取数组元素by index
【参数】:
 pArr: the array's address.
 nIndex: the element's position.
 ppData: out parameter, to record the element's pointer.
【返回值】: true or false.
 ***************************************************************************************************/

cp_bool    DyArrayGetByIndex(DyArray* pArr, cp_int32 nIndex, void** ppData)
{
    //if the input parameter is invalid, return.
    if(!pArr || nIndex < 0 || !ppData || nIndex >= pArr->m_nSize)
    {
		*ppData = NULL;
        return CP_FALSE;
    }
	*ppData = pArr->m_ppData[nIndex];//get the related element.
	return CP_TRUE;
}

/**************************************************************************************************
【函数名】: DyArrayGetFirst
【描述】:获取数组第一个元素
【参数】:
 pArr: the array's address.
 ppData: out parameter, to record the element's pointer.
【返回值】: true or false.
 ***************************************************************************************************/

cp_bool    DyArrayGetFirst(DyArray* pArr,void** ppData)
{
	return DyArrayGetByIndex(pArr,0,ppData) ? CP_TRUE : CP_FALSE;
}

/**************************************************************************************************
【函数名】: DyArrayGetLast
【描述】: 获取数组最后一个元素
【参数】:
 pArr: the array's address.
 ppData: out parameter, to record the element's pointer.
【返回值】: true or false.
 ***************************************************************************************************/

cp_bool    DyArrayGetLast(DyArray* pArr,void** ppData)
{
	return DyArrayGetByIndex(pArr,pArr->m_nSize-1,ppData) ? CP_TRUE : CP_FALSE;
}

/**************************************************************************************************
【函数名】:DyArraySetByIndex
【描述】: 设置数组元素by index
【参数】:
 pArr: the array's address.
 nIndex: the element's position.
 pData: the element's pointer.
【返回值】: true or false.
 ***************************************************************************************************/

cp_bool    DyArraySetByIndex(DyArray* pArr, cp_int32 nIndex, void* pData)
{
    //if the input parameter is invalid, return.
    if(!pArr || nIndex < 0)
    {
        return CP_FALSE;
    }
	pArr->m_ppData[nIndex] = pData;//find the related position and set its value.
	return CP_TRUE;
}

/**************************************************************************************************
【函数名】: DyArrayLength
【描述】:获取数组的长度
【参数】:
 pArr: the array's address.
【返回值】: 数组长度.
 ***************************************************************************************************/

cp_int32  DyArrayLength(DyArray* pArr)
{
	return pArr ? pArr->m_nSize : -1;
}

/**************************************************************************************************
【函数名】: DyArrayFind
【描述】:查找数组中的指定元素
 【参数】:
 pArr: the array's address.
 pCmp: the callback function to compare the data.
 pData: the search destination in the array.
【返回值】:如果成功返回位置，否则返回-1
 ***************************************************************************************************/

cp_int32    DyArrayFind(DyArray* pArr, DataCmpFunc pCmp,void *pData)
{
	cp_int32 i;
    
    //if the input parameter is invalid, return.
    if(!pArr)
    {
        return -1;
    }
    //visit each one to find the right one.
	for(i=0; i<pArr->m_nSize;i++)
	{
	    if(pCmp)
        {
    		if(pCmp(pArr->m_ppData[i],pData) == CP_TRUE)
            {
    			return i;
            }
        }else
        {
            //if NO compare funciton, just compare the address.
            if(pArr->m_ppData[i] == pData)
            {
                return i;
            }
        }
        
	}
	return -1;
}

/**************************************************************************************************
【函数名】: DyArrayForEach
【描述】:遍历数组
【参数】:
 pArr: the array's address.
 pVisit: the callback function to visit the data.
【返回值】:如果成功返回true，否则false
 ***************************************************************************************************/

cp_bool    DyArrayForEach(DyArray* pArr, DataVisitFunc pVisit)
{
	cp_int32 i;
    
    //if the input parameter is invalid, return.
	if(!pArr || !pVisit)
    {
        return CP_FALSE;
    }
    //visit each one with the visit function.
	for(i=0; i<pArr->m_nSize;i++)
	{
		pVisit(pArr->m_ppData[i]);
	}
	return CP_TRUE;
}

/**************************************************************************************************
【函数名】: DyArrayDestroy
【描述】:销毁整个数组
【参数】:
 pArr: the array's address.
【返回值】:NA
 ***************************************************************************************************/

void DyArrayDestroy(DyArray* pArr)
{
	cp_int32 i;
    
    //if the input parameter is invalid, return.
    if(!pArr)
    {
        return;
    }
    //Using destroy function to destroy each element's memory.
	if(pArr->m_fDestroy)
	{
		for(i=0; i<pArr->m_nSize; i++)
		{
			pArr->m_fDestroy(pArr->m_ppData[i]);
		}
	}
    //free the array.
	FREEFUN(pArr->m_ppData);
	pArr->m_ppData = NULL;
	FREEFUN(pArr);
	pArr = NULL;
}

/**************************************************************************************************
【函数名】: DyArrayDestroyCustom
【描述】:使用用户函数，小围数组
 【参数】:
 pArr: the array's address.
 pDataDestroy: user's destroy function.
【返回值】:NA
 ***************************************************************************************************/

void DyArrayDestroyCustom(DyArray* pArr,DataDestroyFunc pDataDestroy)
{
	cp_int32 i;
    
    //if the input parameter is invalid, return.
    if(!pArr)
    {
        return;
    }
    //Using destroy function to destroy each element's memory.
	if(pDataDestroy)
	{
		for(i=0; i<pArr->m_nSize;i++)
		{
			pDataDestroy(pArr->m_ppData[i]);
		}
	}
    //free the array.
	FREEFUN(pArr->m_ppData);
	pArr->m_ppData = NULL;
	FREEFUN(pArr);
}

/**************************************************************************************************
【函数名】: DyArrayExpand
【描述】:扩展数组
【参数】:
 pArr: the array's address.
 nNeed: the needed new size.
【返回值】:如果成功返回ture否则返回false
 ***************************************************************************************************/

cp_bool DyArrayExpand(DyArray* pArr, cp_int32 nNeed)
{
    cp_int32 allocSize = 0;
    void** data = NULL;
    
    //if the input parameter is invalid, return.
	if(!pArr)
    {
        return CP_FALSE;
    }
    //if need, expand to 1.5 times of the original size.
	if((pArr->m_nSize + nNeed) > pArr->m_nAllocSize)
	{
		allocSize = pArr->m_nAllocSize + (pArr->m_nAllocSize>>1);
        data = (void**)REALLOCFUN(pArr->m_ppData, sizeof(void*) * allocSize);
        if(data != NULL)
        {
            //clear the expanded space of the new memory.
            MEMSETFUN(data+pArr->m_nAllocSize,0,(allocSize-pArr->m_nAllocSize)*sizeof(void*));
			pArr->m_ppData = data;
            pArr->m_nAllocSize = allocSize;
		}
	}
	return ((pArr->m_nSize + nNeed) <= pArr->m_nAllocSize) ? CP_TRUE : CP_FALSE;
}

/**************************************************************************************************
【函数名】: DyArrayInsert
【描述】:插入数组by index
 【参数】:
 pArr: the array's address.
 nIndex: the position in the array to insert new data.
 pData: the data to be inserted.
【返回值】:如果成功返回true否则false
 ***************************************************************************************************/

cp_bool DyArrayInsert(DyArray* pArr, cp_int32 nIndex, void* pData)
{
	cp_bool bRet = CP_FALSE;
    cp_int32 nCursor = nIndex;
	cp_int32 i;
    
    //if the input parameter is invalid, return.
	if(!pArr)
    {
        return CP_FALSE;
    }
    //get the right cursor.
    nCursor = nCursor < pArr->m_nSize ? nCursor : pArr->m_nSize;
    if(DyArrayExpand(pArr, 1) == CP_TRUE)
    {
        //move all the elements after the cursor to the next positon.
        for(i = pArr->m_nSize; i > nCursor; i--)
        {
			pArr->m_ppData[i] = pArr->m_ppData[i-1];
        }
        //set the cursor's value.
        pArr->m_ppData[nCursor] = pData;
        pArr->m_nSize++;
        bRet = CP_TRUE;
    }
    return bRet;
}

/**************************************************************************************************
【函数名】: DyArrayPrepend
【描述】:在数组开始添加一个数据
 【参数】:
 pArr: the array's address.
 pData: the data to be added.
【返回值】:如果成功返回ture，否则false
 ***************************************************************************************************/

cp_bool    DyArrayPrepend(DyArray* pArr, void* pData)
{
	return DyArrayInsert(pArr,0,pData) ? CP_TRUE:CP_FALSE;
}

/**************************************************************************************************
【函数名】: DyArrayAppend
 【描述】:添加数据到数组末尾
 【参数】:
 pArr: the array's address.
 pData: the data to be added.
【返回值】:如果成功返回true，否则false
 ***************************************************************************************************/

cp_bool    DyArrayAppend(DyArray* pArr, void* pData)
{
	return  DyArrayInsert(pArr,pArr->m_nSize,pData) ? CP_TRUE:CP_FALSE;
}

/**************************************************************************************************
【函数名】: DyArrayShrink
【描述】:缩减数组
【参数】:
 pArr: the array's address.
【返回值】:ture 或者false
 ***************************************************************************************************/

cp_bool DyArrayShrink(DyArray* pArr)
{
    cp_int32 nAllocSize = 0;
    void** pData = NULL;
    
    //if the input 【参数】 is invalid, return.
	if(!pArr)
    {
        return CP_FALSE;
    }
    //if need, shrink the array to 1.5 times of elements number.
    if((pArr->m_nSize < (pArr->m_nAllocSize >> 1)) && (pArr->m_nAllocSize > MIN_PRE_ALLOCATE_SIZE))
    {
        nAllocSize = pArr->m_nSize + (pArr->m_nSize >> 1);
        pData = (void**)REALLOCFUN(pArr->m_ppData, sizeof(void*) * nAllocSize);
        if(pData != NULL)
        {
            //clear memory of the unused space of new memory.
            MEMSETFUN(pData+pArr->m_nSize,0,(nAllocSize-pArr->m_nSize)*sizeof(void*));
            pArr->m_ppData = pData;
            pArr->m_nAllocSize = nAllocSize;
        }
    }
    return CP_TRUE;
}

/**************************************************************************************************
【函数名】: DyArrayDelete
【描述】:删除元素by index
 【参数】:
 pArr: the array's address.
 nIndex: the position in the array to delete useless data.
【返回值】:ture 或者false
 ***************************************************************************************************/

cp_bool DyArrayDelete(DyArray* pArr, cp_int32 nIndex)
{
    cp_int32 i;
    
    //if the input parameter is invalid, return.
	if(!pArr)
    {
        return CP_FALSE;
    }
    //destroy the element with destroy function.
	if(pArr->m_fDestroy)
	{
		pArr->m_fDestroy(pArr->m_ppData[nIndex]);
	}
    //move the elements after 'nIndex' to the previous one.
    for(i = nIndex; (i+1) < pArr->m_nSize; i++)
    {
        pArr->m_ppData[i] = pArr->m_ppData[i+1];
    }
    //set the last one to null.
	pArr->m_ppData[i] = NULL;
    pArr->m_nSize--;
    //if need ,shrink the size.
    DyArrayShrink(pArr);
    return CP_TRUE;
}
/**************************************************************************************************
 【函数名】: DyArrayDeleteEx
 【描述】:删除元素by index （扩展）
 【参数】:
 pArr: the array's address.
 nIndex: the position in the array to delete useless data.
 nEdn:
 【返回值】:ture 或者false
 ***************************************************************************************************/

cp_bool DyArrayDeleteEx(DyArray* pArr, cp_int32 nBegin,cp_int32 nEnd)
{
	cp_int32 i,nLen = 0;
    
	//if the input parameter is invalid, return.
	//if(!pArr && nBegin>nEnd && nBegin<0 && nBegin>=pArr->m_nSize && nEnd<0 && nEnd>=pArr->m_nSize)
	if(!pArr)
	{
		return CP_FALSE;
	}
	//destroy the element with destroy function.
	if(pArr->m_fDestroy)
	{
		for(i=nBegin; i<=nEnd; i++)
		{
			pArr->m_fDestroy(pArr->m_ppData[i]);
		}
	}
	//move the elements after 'nIndex' to the previous one.
	nLen = nEnd - nBegin + 1;
	for(i = nBegin; (i+nLen) < pArr->m_nSize; i++)
	{
		pArr->m_ppData[i] = pArr->m_ppData[i+nLen];
	}
	//set the last one to null.
	//pArr->m_ppData[i] = NULL;
	pArr->m_nSize -= nLen;
	//if need ,shrink the size.
	DyArrayShrink(pArr);
	return CP_TRUE;
}

/**************************************************************************************************
【函数名】: DyArrayReset
【描述】:清除数组数据，缩减数组到原始大小
【参数】:
 pArr: the array's address.
【返回值】:
 none.
 ***************************************************************************************************/

void DyArrayReset(DyArray* pArr)
{
	cp_int32 i;
	void** pData = NULL;
    
    //if the input parameter is invalid, return.
    if(!pArr)
    {
        return;
    }
    //reset all the elements with destroy function.
	if(pArr->m_fDestroy)
	{
		for(i=0; i<pArr->m_nSize;i++)
		{
			pArr->m_fDestroy(pArr->m_ppData[i]);
		}
	}
	pArr->m_nSize = 0;
    //if need, shrink the size.
	if(pArr->m_nAllocSize > MIN_PRE_ALLOCATE_SIZE)
	{
		pData = (void**)REALLOCFUN(pArr->m_ppData, sizeof(void*) * MIN_PRE_ALLOCATE_SIZE);
        if(pData != NULL)
        {
            pArr->m_ppData = pData;
            pArr->m_nAllocSize = MIN_PRE_ALLOCATE_SIZE;
        }
		if(pArr->m_ppData)
		{
			MEMSETFUN(pArr->m_ppData,0,sizeof(void*)*pArr->m_nAllocSize);
		}
	}
}
/**************************************************************************************************
【函数名】: DyArrayClear
【描述】:清除数组数据，不缩减数组到原始大小
【参数】:
 pArr: the array's address.
【返回值】:NA
 ***************************************************************************************************/

void DyArrayClear(DyArray* pArr)
{
	cp_int32 i;
	void** pData = NULL;
    
	//if the input parameter is invalid, return.
	if(!pArr)
	{
		return;
	}
	//reset all the elements with destroy function.
	if(pArr->m_fDestroy)
	{
		for(i=0; i<pArr->m_nSize;i++)
		{
			pArr->m_fDestroy(pArr->m_ppData[i]);
		}
	}
	pArr->m_nSize = 0;
}

/**************************************************************************************************
【函数名】: DyArrayResetCustom
【描述】:清除数组使用用户函数，缩减数组到原始大小
【参数】:
 pArr: the array's address.
 pDataDestroy: user's destroy function.
【返回值】:NA
 ***************************************************************************************************/

void DyArrayResetCustom(DyArray* pArr,DataDestroyFunc pDataDestroy)
{
	cp_int32 i;
	void** pData = NULL;
    
    //if the input parameter is invalid, return.
    if(!pArr)
    {
        return;
    }
    //reset all the elements with destroy function.
	if(pDataDestroy)
	{
		for(i=0; i<pArr->m_nSize;i++)
		{
			pDataDestroy(pArr->m_ppData[i]);
		}
	}
	pArr->m_nSize = 0;
    //if need, shrink the size.
	if(pArr->m_nAllocSize > MIN_PRE_ALLOCATE_SIZE)
	{
		pData = (void**)REALLOCFUN(pArr->m_ppData, sizeof(void*) * MIN_PRE_ALLOCATE_SIZE);
        if(pData != NULL)
        {
            pArr->m_ppData = pData;
            pArr->m_nAllocSize = MIN_PRE_ALLOCATE_SIZE;
        }
		if(pArr->m_ppData)
		{
			MEMSETFUN(pArr->m_ppData,0,sizeof(void*)*pArr->m_nAllocSize);
		}
	}
}
/**************************************************************************************************
【函数名】: DyArrayClearCustom
【描述】:清除数组使用用户函数，不缩减数组到原始大小
【参数】:
 pArr: the array's address.
 pDataDestroy: user's destroy function.
【返回值】:NA
 ***************************************************************************************************/

void DyArrayClearCustom(DyArray* pArr,DataDestroyFunc pDataDestroy)
{
	cp_int32 i;
	void** pData = NULL;
    
	//if the input parameter is invalid, return.
	if(!pArr)
	{
		return;
	}
	//reset all the elements with destroy function.
	if(pDataDestroy)
	{
		for(i=0; i<pArr->m_nSize;i++)
		{
			pDataDestroy(pArr->m_ppData[i]);
		}
	}
	pArr->m_nSize = 0;
    
}

/*int
 ft_list_eol (const struct ft_list * li, int i)
 {
 if (li == NULL)
 return -1;
 if (i < li->nb_elt)
 return 0;                   // not end of list
 return 1;                     // end of list
 }*/

cp_int32 DyArrayLastElem(DyArray* pArr,cp_int32 nIndex)
{
	if(pArr)
	{
		if(nIndex < pArr->m_nSize)
		{
			return 0;
		}else
		{
			return 1;
		}
	}else
	{
		return -1;
	}
}
