//
//  treeStruct.c
//  dataStruct
//
//  Created by hherima on 14-8-1.
//  Copyright (c) 2014年 . All rights reserved.
//
#include "treeStruct.h"

cp_bool  create_first_array(struct tree *c_tree,DataDestroyFunc data_destroy)
{
    if( c_tree == NULL )
        return CP_FALSE;
    c_tree->first_array = DyArrayCreate(data_destroy);
    if(c_tree->first_array == NULL)
        return CP_FALSE;
    else
        return CP_TRUE;
}

cp_bool create_second_array(struct firstnode *first_node,DataDestroyFunc data_destroy)
{
    if(first_node == NULL)
        return CP_FALSE;
    first_node->second_array = DyArrayCreate(data_destroy);
    if(first_node->second_array == NULL)
        return CP_FALSE;
    else
        return CP_TRUE;
}

cp_bool    append_first_ele( struct tree *c_tree, struct firstnode *first_node )
{
    if( c_tree == NULL || first_node == NULL)
    {
        return CP_FALSE;
    }
    
    if( !DyArrayAppend(c_tree->first_array, first_node) )
        return CP_FALSE;
    else
    {
        return CP_TRUE;
    }
}

cp_bool    append_second_ele(struct firstnode *first_node, struct secondnode *second_node)
{
    if( first_node == NULL || second_node == NULL)
    {
        return CP_FALSE;
    }
    if( !DyArrayAppend(first_node->second_array, second_node))
        return CP_FALSE;
    else
    {
        return CP_TRUE;
    }
}

cp_bool    insert_first_ele(struct tree *c_tree, struct firstnode *first_node, cp_int32 insert_pos)
{
    if( first_node == NULL || c_tree == NULL)
    {
        return CP_FALSE;
    }
    if(!DyArrayInsert(c_tree->first_array, insert_pos, first_node))
        return CP_FALSE;
    else
        return CP_TRUE;
}


cp_bool    insert_second_ele(struct firstnode *first_node, struct secondnode *second_node, cp_int32 insert_pos)
{
    if( first_node == NULL || second_node == NULL)
    {
        return CP_FALSE;
    }
    if(!DyArrayInsert(first_node->second_array, insert_pos, second_node))
        return CP_FALSE;
    else
        return CP_TRUE;
}



void traversal_tree(struct tree *theTree)
{
    cp_int32 i = 0, j = 0;
    cp_int32 first_num = 0, second_num = 0;
    struct firstnode *pcurfirst;
    struct secondnode *pcursecond;
    first_num = theTree->first_array->m_nSize;
    while(i < first_num)
    {
        pcurfirst = (struct firstnode*)(theTree->first_array->m_ppData[i++]);
        // visit(pcurfirst);
        j = 0;
        second_num = pcurfirst->second_array->m_nSize;
        while(j < second_num)
        {
            pcursecond = (struct secondnode*)(pcurfirst->second_array->m_ppData[j++]);
            // visit(pcursecond);
        }
    }
    //遍历结束的回调
}

void traversal_firstnode(struct tree *theTree)
{
    cp_int32 i = 0;
    cp_int32 first_num = 0;
    struct firstnode *pcurfirst;
    first_num = theTree->first_array->m_nSize;
    while(i < first_num)
    {
        pcurfirst = (struct firstnode*)(theTree->first_array->m_ppData[i++]);
        // visit(pcurfirst);
    }
    //遍历结束的回调
}

cp_bool ThisIsSelectedNode(struct tree *theTree, void *pNode)
{
	if(theTree->secondIndex == -1)
	{
		if(theTree->first_array->m_ppData[theTree->firstIndex] == pNode)
		{
			return CP_TRUE;
		}
		else
		{
			return CP_FALSE;
		}
	}
	else
	{
		struct firstnode *first_node = NULL;
		first_node = theTree->first_array->m_ppData[theTree->firstIndex];
		if(first_node->second_array->m_ppData[theTree->secondIndex] == pNode)
		{
			return CP_TRUE;
		}
		else
		{
			return CP_FALSE;
		}
	}
}

void *get_focus_first(struct tree *theTree)
{
	if(theTree == NULL)
		return NULL;
	if(theTree->first_array == NULL)
		return NULL;
	return theTree->first_array->m_ppData[theTree->firstIndex];
}
