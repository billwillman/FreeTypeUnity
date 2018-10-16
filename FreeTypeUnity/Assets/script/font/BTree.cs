using System;
using System.Collections.Generic;
using UnityEngine;

public class PicNode<KEY>
{
    public int width;
    public int height;
    public KEY key = default(KEY);
    // 是否旋转
    public bool IsRot = false;
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

