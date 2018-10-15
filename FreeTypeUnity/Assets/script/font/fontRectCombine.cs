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
    }
}
