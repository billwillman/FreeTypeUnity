using System;
using System.Collections.Generic;
using UnityEngine;

namespace FreeType
{
    // 字体贴图封装
    public class FontTexture
    {
        private FontRectCombine m_Combine = null;
        private Texture2D m_FontTex = null;

        private void DestroyFontTex()
        {
            if (m_FontTex != null)
            {
                GameObject.Destroy(m_FontTex);
                m_FontTex = null;
            }
        }

        private void DestroyFontRectCombine()
        {
            if (m_Combine != null)
            {
                m_Combine.OnDestroy();
                m_Combine = null;
            }
        }

        public void OnDestroy()
        {
            DestroyFontTex();
            DestroyFontRectCombine();
        }

        // 查找文字
        public PicNode<FontRectKey> FindChar(char value, FreeTypeFont font)
        {
            if (m_Combine == null || font == null || font.font == null)
                return null;
            return m_Combine.FindPicNode(value, font.currentSize, font.sizeType, font.hDpi, font.vDpi);
        }

    }
}
