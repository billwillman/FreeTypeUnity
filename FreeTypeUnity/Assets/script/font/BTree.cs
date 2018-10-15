using System;
using System.Collections.Generic;
using UnityEngine;

public class PicNode<KEY>
{
    public int width;
    public int height;
    public KEY key = default(KEY);
}

public class BTreeNode<KEY>
{
    // 开始位置
    public int x, y;
    public PicNode<KEY> virtualPic;
    public bool isRoute;
    public bool isFull;
    public BTreeNode<KEY> left, right;
}

