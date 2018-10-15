//
//  hashStruct.h
//  dataStruct
//
//  Created by hherima on 14-7-29.
//  Copyright (c) 2014年 . All rights reserved.
//

#ifndef dataStruct_hashStruct_h
#define dataStruct_hashStruct_h
#include <stdlib.h>
#include "cpPlatform.h"
#include "dyArray.h"

struct Node
{
    cp_int8* m_pKey; //the hash key.
    cp_int32 m_nKeyLength; // the length of the hash key in bytes.
    void* m_pVal;//hash_node value
    struct Node* m_pNext;
};//hash table，use link list to process conflict

struct HashTable
{
    cp_int32 m_nLength; //hash table's length.
    cp_int32 m_nEleNum; //hash table's element count.
    struct Node **m_ppHead;//the hash table's array to record all key's value.
};

cp_int32 GetHashFileNum(cp_int8* pKey, cp_int32 nKeyLength);

struct Node* HashFindOne(cp_int8* pKey,cp_int32 nKeyLength,struct HashTable *pTable);//search

cp_int32 HashFindMultkeyredund(cp_int8* pKey,cp_int32 nKeyLength,struct HashTable *pTable,struct DynamicArray *pdestArray);
void HashInsertOne(cp_int8* pKey,cp_int32 nKeyLength,void* pVal,struct HashTable *pTable);//insert
void HashInsertOneKeyredund(char* pKey,cp_int32 nKeyLength,void* pVal,struct HashTable *pTable);

void HashDelOne(struct HashTable * pTable,void (*pFreeFunc) (void *),cp_int8 *pKey,cp_int32 nKeyLength);

struct HashTable * HashTableCreate(cp_int32 nKeyNum);
struct Node* HashGetFirst(struct HashTable *pTable);
struct Node* HashGetNext(struct HashTable *pTable,cp_int8* pKey,cp_int32 nKeyLength);

cp_int32 HashGetLength(struct HashTable *pTable);
void HashTableVisit(struct HashTable * pTable,void (*pVisitFunc) (void *,void *),void *pAgent);
void HashTableReset(struct HashTable * pTable,void (*pFreeFunc) (void *));

void HashTableDestroy(struct HashTable * pTable,void (*pFreeFunc) (void *));

cp_int32 HashGetValue(cp_int8* pKey,cp_int32 nKeyLength,cp_int32 nTableLength);

#endif
