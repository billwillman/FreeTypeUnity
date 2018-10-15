using System;
using System.Collections.Generic;

namespace FreeType
{
    // 三种不同合并算法
    public enum RectCombineType
    {
        left,
        right,
        middle,
        level
    }

    // 字体区域合并
    public class FontRectCombine
    {
        private RectCombineType m_CombineType = RectCombineType.right;
        // 根节点
        private BTreeNode<FontRectKey> m_Root = null;
        private int m_MaxWidth = 1024;
        private int m_MaxHeight = 1024;
        private PicNode<FontRectKey> m_CurrentPic = null;

        public FontRectCombine(int maxWidth = 1024, int maxHeight = 1024, RectCombineType combineType = RectCombineType.right)
        {
            m_MaxWidth = maxWidth;
            m_MaxHeight = maxHeight;
            m_CombineType = combineType;
        }
    }
}
