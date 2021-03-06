﻿using System;
using System.Collections.Generic;

namespace FreeType
{
    // 三种不同合并算法
    public enum RectCombineType
    {
        left,
        right,
        middle
    }

    // 字体区域合并
    public class FontRectCombine
    {
        private RectCombineType m_CombineType = RectCombineType.middle;
        // 根节点
        private BTreeNode<FontRectKey> m_Root = null;
        private int m_MaxWidth = 1024;
        private int m_MaxHeight = 1024;
        private PicNode<FontRectKey> m_CurrentPic = null;
        private Dictionary<FontRectKey, PicNode<FontRectKey>> m_PicNodeMap = new Dictionary<FontRectKey, PicNode<FontRectKey>>();
        // 查找专用
        private FontRectKey m_FindKey = new FontRectKey();

        public FontRectCombine(int maxWidth = 1024, int maxHeight = 1024, RectCombineType combineType = RectCombineType.right)
        {
            m_MaxWidth = maxWidth;
            m_MaxHeight = maxHeight;
            m_CombineType = combineType;
        }

        public int NodeCount
        {
            get
            {
                return m_PicNodeMap.Count;
            }
        }

        public void ForEachBTree(Action<BTreeNode<FontRectKey>> onCallBack)
        {
            if (onCallBack == null || m_Root == null)
                return;
       
          //  ForEachBTree(m_Root.left, onCallBack);
           // ForEachBTree(m_Root.right, onCallBack);
            ForEachBTree(m_Root, onCallBack);
        }

        private void ForEachBTree(BTreeNode<FontRectKey> node, Action<BTreeNode<FontRectKey>> onCallBack)
        {
            if (node == null || onCallBack == null)
                return;
            if (node.left != null)
                ForEachBTree(node.left, onCallBack);
            if (node.virtualPic != null && node.virtualPic.key != null)
                onCallBack(node);
            if (node.right != null)
                ForEachBTree(node.right, onCallBack);
        }

        /// <summary>
        /// 重建字体, 先实现功能，后面可以考虑优化GC
        /// </summary>
        /// <param name="maxWidth">重建设置最大宽</param>
        /// <param name="maxHeight">重建设置最大高</param>
        /// <returns></returns>
        public bool ReBuild(int maxWidth, int maxHeight)
        {
            m_MaxWidth = maxWidth;
            m_MaxHeight = maxHeight;

            var oldMap = m_PicNodeMap;

            m_PicNodeMap = new Dictionary<FontRectKey, PicNode<FontRectKey>>();
            m_Root = null;
            m_CurrentPic = null;

            var iter = oldMap.GetEnumerator();
            while (iter.MoveNext())
            {
                var node = iter.Current.Value;
                if (node != null && node.key != null)
                    InsertNode(node.key.value, node.key.fontSize, node.key.fontSizeType, node.key.hDpi, node.key.vDpi, node.width, node.height);
            }
            iter.Dispose();

            return true;
        }

        // 查找
        public PicNode<FontRectKey> FindPicNode(char value, uint fontSize, FreeTypeSizeType fontSizeType, uint hDpi, uint vDpi)
        {
            m_FindKey.value = value;
            m_FindKey.fontSizeType = fontSizeType;
            m_FindKey.hDpi = hDpi;
            m_FindKey.vDpi = vDpi;
            PicNode<FontRectKey> ret;
            if (m_PicNodeMap.TryGetValue(m_FindKey, out ret))
                return ret;
            return null;
        }

        public bool InsertNode(char value, uint fontSize, FreeTypeSizeType fontSizeType, uint hDpi, uint vDpi, int width, int height)
        {
            // 后面考虑通过池中取
            FontRectKey key = new FontRectKey();
            key.value = value;
            key.fontSize = fontSize;
            key.fontSizeType = fontSizeType;
            key.hDpi = hDpi;
            key.vDpi = vDpi;

            return InsertNode(key, width, height);
        }

        private bool InsertNode(FontRectKey key, int width, int height)
        {
            if (key == null)
                return false;
            PicNode<FontRectKey> newNode = new PicNode<FontRectKey>();
            newNode.key = key;
            newNode.width = width;
            newNode.height = height;
            bool ret = InsertNode(newNode);
            if (!ret && !newNode.IsRot)
            {
                newNode.IsRot = true;
                newNode.width = height;
                newNode.height = width;
                ret = InsertNode(newNode);
            }
            if (ret)
            {
                m_PicNodeMap[key] = newNode;
            }
            return ret;
        }

        // 插入节点
        private bool InsertNode(PicNode<FontRectKey> newNode)
        {
            if (newNode == null)
                return false;
            Func<BTreeNode<FontRectKey>, bool> func = null;
            switch (m_CombineType)
            {
                case RectCombineType.left:
                    func = preTraveralTree;
                    break;
                case RectCombineType.middle:
                    func = midTraveralTree;
                    break;
                case RectCombineType.right:
                    func = lastTraveralTree;
                    break;
                default:
                    return false;
            }
            bool ret = false;
            if (func != null)
            {
                InitRoot();
                m_CurrentPic = newNode;
                ret = func(m_Root);
            }
            return ret;
        }

        private void InitRoot()
        {
            if (m_Root == null)
            {
                m_Root = new BTreeNode<FontRectKey>();
                m_Root.x = 0; m_Root.y = 0;
                m_Root.virtualPic = new PicNode<FontRectKey>();
                m_Root.virtualPic.width = m_MaxWidth;
                m_Root.virtualPic.height = m_MaxHeight;
            }
        }

        private bool preTraveralTree(BTreeNode<FontRectKey> newNode)
        {
            if (newNode == null)
                return false;
            bool ret = preTraveralTree(newNode.left);
            if (ret)
                return ret;
            ret = insertPicture(newNode);
            if (ret)
                return ret;
            ret = preTraveralTree(newNode.right);
            return ret;
        }


        private bool midTraveralTree(BTreeNode<FontRectKey> newNode)
        {
            if (newNode == null)
                return false;
            bool ret = insertPicture(newNode);
            if (ret)
                return ret;
            ret = midTraveralTree(newNode.left);
            if (ret)
                return ret;
            ret = midTraveralTree(newNode.right);
            return ret;
        }

        // 
        private bool lastTraveralTree(BTreeNode<FontRectKey> newNode)
        {
            if (newNode == null)
                return false;
            bool ret = lastTraveralTree(newNode.right);
            if (ret)
                return ret;
            ret = insertPicture(newNode);
            if (ret)
                return ret;
            ret = lastTraveralTree(newNode.left);
            return ret;
        }

        // 这个函数属于核心函数
        private bool insertPicture(BTreeNode<FontRectKey> node)
        {
            /*
         拆分剩余rect为left和right两个分支。
         ●---------●-----------------
         | picture |   right        |
         |         |                |
         ●---------------------------
         |                          |
         |        left              |
         |                          |
         |                          |
         |                          |
         ----------------------------
         例如.picture已经占据了【左上角】区域。剩下的区域分为left和right。点（●）的地方就是CGPoint了。
         ● 优化点：如果picture是矩形，那么在生成left和right的时候。可以有两个选择：向下延伸，向右延伸。
         通常是向值小的一方延伸，这样保证值大的一方可以放进去更多的图片。
         ● 上面的例子是向右延伸。
         */

            if (node == null)
                return false;

            if (!node.isFull &&
                node.virtualPic.width >= m_CurrentPic.width &&
                node.virtualPic.height >= m_CurrentPic.height)
            {
                // 是否已经填充
                node.isFull = true;
                // 后面考虑用池来做
                node.left = new BTreeNode<FontRectKey>();
                node.left.x = node.x;
                node.left.y = node.y + m_CurrentPic.height;
                // 后面考虑用池来做
                node.left.virtualPic = new PicNode<FontRectKey>();

                // 后面考虑用池来做
                node.right = new BTreeNode<FontRectKey>();
                node.right.x = node.x + m_CurrentPic.width;
                node.right.y = node.y;
                // 后面考虑用池来做
                node.right.virtualPic = new PicNode<FontRectKey>();

                if (m_CurrentPic.width >= m_CurrentPic.height)
                {
                    node.left.virtualPic.width = node.virtualPic.width;
                    node.left.virtualPic.height = node.virtualPic.height - m_CurrentPic.height;

                    node.right.virtualPic.width = node.virtualPic.width - m_CurrentPic.width;
                    node.right.virtualPic.height = m_CurrentPic.height;
                } else
                {
                    node.left.virtualPic.width = m_CurrentPic.width;
                    node.left.virtualPic.height = node.virtualPic.height - m_CurrentPic.height;

                    node.right.virtualPic.width = node.virtualPic.width - m_CurrentPic.width;
                    node.right.virtualPic.height = node.virtualPic.height;
                }

                node.virtualPic = m_CurrentPic;

                return true;
            }


            return false;
        }

        public void OnDestroy()
        {
            // 暂时这样后面考虑回池等
            m_Root = null;
            m_CurrentPic = null;
            if (m_PicNodeMap != null)
                m_PicNodeMap.Clear();
        }

    }
}
