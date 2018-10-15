//
//  hashStruct.c
//  dataStruct
//
//  Created by hherima on 14-7-29.
//  Copyright (c) 2014年 . All rights reserved.
//
#include "hashStruct.h"

#define MAX_HASH_PRIME_ARRAY_NUM    7
/**************************************************************************************************
 function name:
 HashGetValue
 description:
 the hash arithmetic to get the position of the certain key.
 parameter:
 pKey: the exclusive symbol which is related to a data block in hash table.
 nKeyLength: the key string's length.
 nTableLength: the hash table's length.
 return value:
 the position of the certain key.
 ***************************************************************************************************/

cp_int32 HashGetValue(cp_int8* pKey,cp_int32 nKeyLength,cp_int32 nTableLength)
{
	cp_uint32 h = 0;
	cp_uint32 g = 0;
    
	if(!pKey || nKeyLength<1 || nTableLength<1) //if the input parameter is invalid, return.
    {
        return -1;
    }
	while(nKeyLength--) // get each charactor and use it to compute hash value.
	{
		h = (h<<4) + *pKey++;
		g = h & 0xF0000000L;
		if(g)
		{
			h ^= g>>24;
		}
		h &= ~g;
	}
	return h % nTableLength;
}

/**************************************************************************************************
 function name:
 HashFindOne
 description:
 search the position's node of the certain key.
 parameter:
 pKey: the exclusive symbol which is related to a data block in hash table.
 nKeyLength: the key string's length.
 pTable: the hash table.
 return value:
 the node pointer or null.
 ***************************************************************************************************/

struct Node* HashFindOne(cp_int8* pKey,cp_int32 nKeyLength,struct HashTable *pTable)//search
{
    cp_int32 nPos = 0;
	struct Node* pCur = NULL;
    
    //if the input parameter is invalid, return.
	if(!pTable || !pKey || nKeyLength<1)
    {
        return NULL;
    }
    nPos = HashGetValue(pKey,nKeyLength,pTable->m_nLength);
    if(nPos>=0)
    	pCur = pTable->m_ppHead[nPos];
    //cur = table->head[hash_get_value(key,key_length,table->length)];
	while(pCur) // if has link list, visit all the list to find the right one.
	{
		if(pCur->m_nKeyLength == nKeyLength && MEMCMPFUN(pCur->m_pKey,pKey,nKeyLength) == 0)
		{
			return pCur;
		}
		pCur = pCur->m_pNext;
	}
	return NULL;
}

/**************************************************************************************************
 function name:
 HashFindMultkeyredund
 description:
 search the node of the certain key, there will be several one.
 parameter:
 pKey: the exclusive symbol which is related to several data block in hash table.
 nKeyLength: the key string's length.
 pTable: the hash table.
 pdestArray: the dynamic array which is used to save results and need be initilalized.
 return value:
 the node pointer or null.
 ***************************************************************************************************/

cp_int32 HashFindMultkeyredund(cp_int8* pKey,cp_int32 nKeyLength,struct HashTable *pTable,struct DynamicArray *pDestArray) //search ,the key is redundant.
{
	int nResNum = 0;
	struct Node* pCur = NULL;
    
    //if the input parameter is invalid, return.
	if(!pTable || !pKey || nKeyLength<1 || !pDestArray)
    {
        return -1;
    }
    pCur = pTable->m_ppHead[HashGetValue(pKey,nKeyLength,pTable->m_nLength)];
	while(pCur) //if has link list, visit all the list and find the right one.
	{
		if(pCur->m_nKeyLength == nKeyLength && MEMCMPFUN(pCur->m_pKey,pKey,nKeyLength) == 0)
		{
			DyArrayAppend(pDestArray, pCur->m_pVal); // put the right one to array.
			nResNum++;
			//return cur;
		}
		pCur = pCur->m_pNext;
	}
	return nResNum;
}

/**************************************************************************************************
 function name:
 hashExpand
 description:
 expand the array when it's too small.THIS FUNCTION CAN'T BE USED BECAUSE HASH VALUE IS
 CHANGED WHEN TABLE LENGTH CHANGED.
 parameter:
 pTable: the hash table.
 nNeed: the needed new size.
 return value:
 if succeed,return the true, else, return false.
 ***************************************************************************************************/

cp_bool HashExpand(struct HashTable * pTable, cp_int32 nNeed)
{
	cp_int32 i;
    struct Node ** pData = NULL;
    cp_int32 nAllocSize = 0;
	cp_int32 nPrime[MAX_HASH_PRIME_ARRAY_NUM] = {
		17,   //0
		37,   //1
		79,   //2
        
		163,  //3
		331,  //4
		673,  //5
        
		1361  //6
	};//The prime table used to be the length of hash table to decrease conflict.
    
    //if the input parameter is invalid, return.
	if(!pTable || nNeed<1)
    {
        return CP_FALSE;
    }
    //if need, expand to one and half times of original size.
	if(((pTable->m_nEleNum + nNeed) + ((pTable->m_nEleNum + nNeed)>>1) ) > pTable->m_nLength)
	{
		nAllocSize = pTable->m_nLength + (pTable->m_nLength>>1);
		for(i=0; i<MAX_HASH_PRIME_ARRAY_NUM; i++) //find the nearest one of prime array.
		{
			if(nPrime[i] > nAllocSize)
			{
				nAllocSize = nPrime[i];
				break;
			}
		}
        pData = (struct Node **)REALLOCFUN(pTable->m_ppHead, sizeof(struct Node *) * nAllocSize);
        if(pData != NULL)
        {
            // clear the expanded space.
            MEMSETFUN(pData+pTable->m_nLength,0,(nAllocSize-pTable->m_nLength)*sizeof(struct Node *));
            pTable->m_ppHead = pData;
            pTable->m_nLength = nAllocSize;
		}
	}
	return ((pTable->m_nEleNum + nNeed) + ((pTable->m_nEleNum + nNeed)>>1) <= pTable->m_nLength) ? CP_TRUE : CP_FALSE;
}

/**************************************************************************************************
 function name:
 HashInsertOne
 description:
 insert the node of the certain key.
 parameter:
 pKey: the exclusive symbol which is related to a data block in hash table.
 nKeyLength: the key string's length.
 pVal: the node pointer of the certain key.
 pTable: the hash table.
 return value:
 none.
 ***************************************************************************************************/

void HashInsertOne(cp_int8* pKey,cp_int32 nKeyLength,void* pVal,struct HashTable *pTable)//insert
{
	cp_int32 nPos = 0;
	struct Node** pNode = NULL;
	struct Node* pTmp = NULL;
    
    //if the input parameter is invalid, return.
    if(!pTable || !pKey || nKeyLength<1)
    {
        return ;
    }
    //comment it because when it expands, the same key's position changed and the original key position CAN'T be found.
	/*if((pTable->m_EleNum + 1) + ((pTable->m_EleNum + 1)>>1) > pTable->m_nLength)
     {
     HashExpand(pTable, 1);
     }*/
	//compute the hash position.
	pTable->m_nEleNum++;
	nPos = HashGetValue(pKey,nKeyLength,pTable->m_nLength);
	pNode = &pTable->m_ppHead[nPos];
    
    //if this key is NOT exist, insert it.
	if(HashFindOne(pKey,nKeyLength,pTable) == NULL)
	{
	    //malloc a new node and set the value.
		pTmp=(struct Node*)MALLOCFUN(sizeof(struct Node));
		MEMSETFUN(pTmp,0,sizeof(struct Node));
		pTmp->m_pKey = (char*)MALLOCFUN(nKeyLength+2);//for Unicode, two bytes zero is needed.
		MEMSETFUN(pTmp->m_pKey,0,nKeyLength+2);
		MEMCPYFUN(pTmp->m_pKey,pKey,nKeyLength);
		pTmp->m_nKeyLength = nKeyLength;
		pTmp->m_pVal = pVal;
		pTmp->m_pNext=NULL;
        //if there is a list, then insert to the tail.
		while(*pNode)
		{
			pNode = &((*pNode)->m_pNext);
		}
		*pNode = pTmp;
	}
}

/**************************************************************************************************
 function name:
 HashInsertOneKeyredund
 description:
 insert the node of the certain key.
 parameter:
 pKey: the symbol which is related to a data block in hash table.
 nKeyLength: the key string's length.
 pVal: the node pointer of the certain key.
 pTable: the hash table.
 return value:
 none.
 ***************************************************************************************************/

void HashInsertOneKeyredund(cp_int8* pKey,cp_int32 nKeyLength,void* pVal,struct HashTable *pTable) //insert,key is redundant.
{
	cp_int32 nPos = 0;
	struct Node** pNode = NULL;
	struct Node* pTmp = NULL;
    
    //if the input parameter is invalid, return.
    if(!pTable || !pKey || nKeyLength<1)
    {
        return ;
    }
    //comment it because when it expands, the same key's position changed and the original key position CAN'T be found.
	/*if((table->ele_num + 1) + ((table->ele_num + 1)>>1) > table->length)
     {
     hash_expand(table, 1);
     }*/
	//compute the hash position.
	pTable->m_nEleNum++;
	nPos= HashGetValue(pKey,nKeyLength,pTable->m_nLength);
	pNode = &pTable->m_ppHead[nPos];
    
    //compare with HashInsertOne, comment this line. if(hash_find_one(key,key_length,table) == NULL)
	{
	    //malloc a new node and set the value.
		pTmp=(struct Node*)MALLOCFUN(sizeof(struct Node));
		MEMSETFUN(pTmp,0,sizeof(struct Node));
		pTmp->m_pKey = (char*)MALLOCFUN(nKeyLength+2);//for Unicode, two bytes zero is needed.
		MEMSETFUN(pTmp->m_pKey,0,nKeyLength+2);
		MEMCPYFUN(pTmp->m_pKey,pKey,nKeyLength);
		pTmp->m_nKeyLength = nKeyLength;
		pTmp->m_pVal = pVal;
		pTmp->m_pNext=NULL;
        //if has a link list, then insert the new node to the tail.
		while(*pNode)
		{
			pNode = &((*pNode)->m_pNext);
		}
		*pNode = pTmp;
	}
}

/**************************************************************************************************
 function name:
 HashTableCreate
 description:
 create the hash table when the program starts.
 parameter:
 nKeyNum: the key count of the program's data.
 return value:
 the hash table.
 ***************************************************************************************************/

struct HashTable * HashTableCreate(cp_int32 nKeyNum)
{
	struct HashTable * pTable = NULL;
	cp_int32 i;
	cp_int32 nPrime[MAX_HASH_PRIME_ARRAY_NUM] = {
		17,   //0
		37,   //1
		79,   //2
        
		163,  //3
		331,  //4
		673,  //5
        
		1361  //6
	};//The prime table used to be the length of hash table to decrease conflict.
    
    //if the input parameter is invalid, return.
    if(nKeyNum < 1)
    {
        return NULL;
    }
	pTable = (struct HashTable *)MALLOCFUN(sizeof(struct HashTable));
	if(!pTable)
    {
		return NULL;
    }
	MEMSETFUN(pTable,0,sizeof(struct HashTable));
    //The default length is 1.5 times of key's number.
	pTable->m_nLength = nKeyNum + (nKeyNum<<1);
    //find the nearest size of prime array.
	for(i=0; i<MAX_HASH_PRIME_ARRAY_NUM; i++)
	{
		if(nPrime[i] > pTable->m_nLength)
		{
			pTable->m_nLength = nPrime[i];
			break;
		}
	}
	pTable->m_ppHead = (struct Node **) MALLOCFUN(sizeof(struct Node *)*pTable->m_nLength);
	if(!pTable->m_ppHead)
	{
		FREEFUN(pTable);
		return NULL;
	}
	MEMSETFUN(pTable->m_ppHead,0,sizeof(struct Node *)*pTable->m_nLength);
	return pTable;
}
/**************************************************************************************************
 function name:
 HashTableVisit
 description:
 visit all the elements of the hash table.
 parameter:
 pTable: the hash table.
 pVisitFunc: the visit function for each element of the hash table, the first parameter is hash's element,
 the second parameter is 'agent' which is to pass to caller.
 pAgent: used to pass to the call back funtion.
 return value:
 none
 ***************************************************************************************************/

void HashTableVisit(struct HashTable * pTable,void (*pVisitFunc) (void *,void *),void *pAgent)
{
	cp_int32 i;
	struct Node * pTmp = NULL;
    
    //if the input parameter is invalid, return.
    if(!pTable)
    {
        return ;
    }
    //visit each position if it's not null.
	for(i=0; i<pTable->m_nLength; i++)
	{
		if(pTable->m_ppHead[i] == NULL)
        {
            continue;
        }
		if(pTable->m_ppHead[i]->m_pKey)
		{
			if(pVisitFunc)
			{
				pVisitFunc(pTable->m_ppHead[i]->m_pVal,pAgent);
			}
			pTmp = pTable->m_ppHead[i]->m_pNext;
            //if has link list, then visit the whole list.
			while(pTmp)
			{
				if(pVisitFunc)
				{
					pVisitFunc(pTmp->m_pVal,pAgent);
				}
				pTmp = pTmp->m_pNext;
			}
		}
	}
	return ;
}

/**************************************************************************************************
 function name:
 HashGetFirst
 description:
 get the first element of the hash table.
 parameter:
 pTable: the hash table.
 return value:
 the first element
 ***************************************************************************************************/

struct Node* HashGetFirst(struct HashTable *pTable)
{
	cp_int32 i;
    
    //if the input parameter is invalid, return.
    if(!pTable)
    {
        return NULL;
    }
    //find the first not null element of head array.
	for(i=0; i<pTable->m_nLength; i++)
	{
		if(pTable->m_ppHead[i] == NULL)
        {
            continue;
        }
		if(pTable->m_ppHead[i]->m_pKey)
		{
			return pTable->m_ppHead[i];
		}
	}
	return NULL;
}

/**************************************************************************************************
 function name:
 HashGetNext
 description:
 get the next element of the current node which key is given.
 parameter:
 pTable: the hash table.
 pKey: the exclusive symbol which is related to a data block in hash table.
 nKeyLength: the key string's length.
 return value:
 the next element
 ***************************************************************************************************/

struct Node* HashGetNext(struct HashTable *pTable,cp_int8* pKey,cp_int32 nKeyLength)
{
    struct Node* pNext = NULL;
    struct Node* pCur = NULL;
    cp_int32 nPos;
    cp_int32 i;
    
    //if the input parameter is invalid, return.
    if(!pTable)
    {
        return NULL;
    }
    //get the position of the key.
    nPos = HashGetValue(pKey,nKeyLength,pTable->m_nLength);
    if(nPos == -1)
    {
        return NULL;
    }
    pCur = pTable->m_ppHead[nPos];
    if(!pCur)
    {
        return NULL;//the related node of the pKey is NOT exist, so return null.
    }
    //find the right one whose key is same with pKey.
    while(pCur)
    {
        if(pCur->m_nKeyLength == nKeyLength && MEMCMPFUN(pCur->m_pKey,pKey,nKeyLength) == 0)
        {
            break;
        }
        pCur = pCur->m_pNext;
    }
    //get the next pointer directly.
    if(pCur && pCur->m_pNext)
    {
        pNext = pCur->m_pNext;
    }
    else
    {
        //get the next not null one from the head array.
        nPos++;
        for(i=nPos; i<pTable->m_nLength; i++)
        {
            if(pTable->m_ppHead[i] == NULL)
            {
                continue;
            }
            if(pTable->m_ppHead[i]->m_pKey)
            {
                pNext = pTable->m_ppHead[i];
                break;
            }
        }
    }
    return pNext;
}

/**************************************************************************************************
 function name:
 HashTableReset
 description:
 clear the hash table.
 parameter:
 pTable: the hash table.
 pFreeFunc: the free function for hash data "val" which is given by caller.
 return value:
 none
 ***************************************************************************************************/

void HashTableReset(struct HashTable * pTable,void (*pFreeFunc) (void *))
{
	cp_int32 i;
	struct Node * pTmp = NULL;
	struct Node * pTmp1 = NULL;
    
    //if the input parameter is invalid, return.
    if(!pTable)
    {
        return;
    }
    //reset each element of the head array and free related memory.
	for(i=0; i<pTable->m_nLength; i++)
	{
		if(pTable->m_ppHead[i] == NULL)
        {
            continue;
        }
		if(pTable->m_ppHead[i]->m_pKey)
		{
			FREEFUN(pTable->m_ppHead[i]->m_pKey);
			if(pFreeFunc)
			{
				pFreeFunc(pTable->m_ppHead[i]->m_pVal);
			}
			pTmp = pTable->m_ppHead[i]->m_pNext;
			FREEFUN(pTable->m_ppHead[i]);
			pTable->m_ppHead[i] = NULL;
            //free all the link list.
			while(pTmp)
			{
				FREEFUN(pTmp->m_pKey);
				if(pFreeFunc)
				{
					pFreeFunc(pTmp->m_pVal);
				}
				pTmp1 = pTmp;
				pTmp = pTmp->m_pNext;
				FREEFUN(pTmp1);
			}
		}
	}
    //clear the table.
	MEMSETFUN(pTable->m_ppHead,0,sizeof(struct Node *)*pTable->m_nLength);
	pTable->m_nEleNum = 0;
	return ;
}

/**************************************************************************************************
 function name:
 HashTableDestroy
 description:
 destroy the hash table when the program exits.
 parameter:
 pTable: the hash table.
 pFreeFunc: the free function for hash data "val" which is given by caller.
 return value:
 none
 ***************************************************************************************************/

void HashTableDestroy(struct HashTable * pTable,void (*pFreeFunc) (void *))
{
	cp_int32 i;
	struct Node * pTmp = NULL;
	struct Node * pTmp1 = NULL;
    
    //if the input parameter is invalid, return.
    if(!pTable)
    {
        return;
    }
    //clear each element and free its memory.
	for(i=0; i<pTable->m_nLength; i++)
	{
		if(pTable->m_ppHead[i] == NULL)
        {
            continue;
        }
		if(pTable->m_ppHead[i]->m_pKey)
		{
			FREEFUN(pTable->m_ppHead[i]->m_pKey);
			if(pFreeFunc)
			{
				pFreeFunc(pTable->m_ppHead[i]->m_pVal);
			}
			pTmp = pTable->m_ppHead[i]->m_pNext;
			FREEFUN(pTable->m_ppHead[i]);
			pTable->m_ppHead[i] = NULL;
            //free the link list.
			while(pTmp)
			{
				FREEFUN(pTmp->m_pKey);
				if(pFreeFunc)
				{
					pFreeFunc(pTmp->m_pVal);
				}
				pTmp1 = pTmp;
				pTmp = pTmp->m_pNext;
				FREEFUN(pTmp1);
			}
		}
	}
    //free the table.
	FREEFUN(pTable->m_ppHead);
	pTable->m_ppHead = NULL;
	FREEFUN(pTable);
	return ;
}

/**************************************************************************************************
 function name:
 HashDelOne
 description:
 delete one node of hash table.
 parameter:
 pTable: the hash table.
 pFreeFunc: the free function for hash data "val" which is given by caller.
 pKey: the exclusive symbol which is related to a data block in hash table.
 nKeyLength: the key string's length.
 return value:
 none
 ***************************************************************************************************/

void HashDelOne(struct HashTable * pTable,void (*pFreeFunc) (void *),char *pKey,cp_int32 nKeyLength)
{
	cp_int32 nPos = 0;
	struct Node *pTmp = NULL;
	struct Node **pTmp1 = NULL;
	struct Node *pTmp2 = NULL;
    
    //if the input parameter is invalid, return.
    if(!pTable || !pKey || nKeyLength<1)
    {
        return;
    }
    //compute the hash position.
    nPos = HashGetValue(pKey,nKeyLength,pTable->m_nLength);
	if(!pTable->m_ppHead[nPos])
    {
        return;//the related node of the key is NOT exist, return.
    }
    //the first one is the right one.
	if(pTable->m_ppHead[nPos]->m_nKeyLength == nKeyLength && MEMCMPFUN(pTable->m_ppHead[nPos]->m_pKey,pKey,nKeyLength) == 0)
	{
		pTable->m_nEleNum--;
		FREEFUN(pTable->m_ppHead[nPos]->m_pKey);
		pTable->m_ppHead[nPos]->m_pKey = NULL;
		if(pFreeFunc)
			pFreeFunc(pTable->m_ppHead[nPos]->m_pVal);
		pTable->m_ppHead[nPos]->m_pVal = NULL;
		if(pTable->m_ppHead[nPos]->m_pNext)
		{
			pTmp = pTable->m_ppHead[nPos];
			pTable->m_ppHead[nPos] = pTable->m_ppHead[nPos]->m_pNext;
			FREEFUN(pTmp);
		}
		else
		{
			FREEFUN(pTable->m_ppHead[nPos]);
			pTable->m_ppHead[nPos] = NULL;
		}
	}
	else
	{
	    //find the right one in the link list.
		pTmp1 = &(pTable->m_ppHead[nPos]->m_pNext);
		while(*pTmp1)
		{
			if((*pTmp1)->m_nKeyLength == nKeyLength && MEMCMPFUN((*pTmp1)->m_pKey,pKey,nKeyLength) == 0)
			{
				//find it, free it and relink the link list.
				pTable->m_nEleNum--;
				FREEFUN((*pTmp1)->m_pKey);
				(*pTmp1)->m_pKey = NULL;
				if(pFreeFunc)
					pFreeFunc((*pTmp1)->m_pVal);
				(*pTmp1)->m_pVal = NULL;
				if((*pTmp1)->m_pNext)
				{
					pTmp2 = *pTmp1;
					*pTmp1 = (*pTmp1)->m_pNext;
					FREEFUN(pTmp2);
				}
				else
				{
					FREEFUN(*pTmp1);
					*pTmp1 = NULL;
				}
				break;
			}
			else
			{
				pTmp1 = &((*pTmp1)->m_pNext);
			}
		}
	}
	return ;
}

/**************************************************************************************************
 function name:
 HashGetLength
 description:
 get the total length of the hash table.
 parameter:
 pTable: the hash table.
 return value:
 none
 ***************************************************************************************************/

cp_int32 HashGetLength(struct HashTable *pTable)
{
    return pTable ? pTable->m_nEleNum : -1;
}

