//
//  treeStruct.h
//  dataStruct
//
//  Created by hherima on 14-8-1.
//  Copyright (c) 2014年 . All rights reserved.
//

#ifndef dataStruct_treeStruct_h
#define dataStruct_treeStruct_h

#include <stdlib.h>
#include "cpPlatform.h"
#include "dyArray.h"

struct firstnode;
struct secondnode;
struct tree;

enum nodetype	//tree节点类型
{
	second_type_node,
	first_type_node
};

struct firstnode
{
    void**  pfirst;
    struct DynamicArray *second_array;
    void *puiData;
    cp_bool flag_expand;    //标志该组是否展开
};


struct TreeNode
{
    enum nodetype pnode_t;         //用来记录该节点为gruop或者是second
    void *nodedata;        //该指针实际应该为firstnode或者secondnode，应根据nodetype强转加以使用
};

    
    struct tree
    {
        /*struct Iterator_trees_fromcur_skipmode */void *piterator_fromcur_skipmode;
        /*struct Iterator_trees_fromhead_skipmode*/void *piterator_fromhead_skipmode;
        /*struct Iterator_trees_fromhead_holemode*/void *piterator_fromhead_holemode;
        
#ifdef FET_ITERATOR_EXTEND
        /*struct Iterator_trees_fromcur_holemode*/void *piterator_fromcur_holemode;
        /*struct Iterator_trees_fromcur_first*/void *piterator_fromcur_first;
        /*struct Iterator_trees_fromhead_first*/void *piterator_fromhead_first;
        /*struct Iterator_trees_fromcur_skipmode_wm*/void *piterator_fromcur_skipmode_wm;
        /*struct Iterator_trees_fromcur_holdmode_wm*/void *piterator_fromcur_holemode_wm;
        /*struct Iterator_trees_fromcur_first_wm*/void *piterator_fromcur_first_wm;
#endif
        struct DynamicArray *first_array;
        cp_int32 firstIndex;  //该second所在组在整个组动态数组中的index
        cp_int32 secondIndex; //该second所在second动态数组中的index
        void * pCursorfirstNode;
        void * pCursorsecondNode;
    };
    
    enum travmode	//遍历模式
    {
        skipModeFlag,	//跳跃闭合组模式
        wholeModeFlag,	//全节点遍历模式（不区分闭合组）
    };
    
    //为树上的节点申请空间
    cp_bool  create_first_array(struct tree *c_tree,DataDestroyFunc data_destroy);
    
    cp_bool  create_second_array(struct firstnode *first_node,DataDestroyFunc data_destroy);
    
    cp_bool	append_first_ele(struct tree *c_tree, struct firstnode *first_node);
    
    cp_bool	append_second_ele(struct firstnode *first_node, struct secondnode *second_node);
    
    cp_bool	insert_first_ele(struct tree *c_tree, struct firstnode *first_node, cp_int32 insert_pos);
    
    cp_bool	insert_second_ele(struct firstnode *first_node, struct secondnode *second_node, cp_int32 insert_pos);
    
    cp_bool ThisIsSelectedNode(struct tree *theTree, void *pNode);
    
    void *get_focus_first(struct tree *theTree);


#endif
