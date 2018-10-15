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
        private int m_MaxWidth = 256;
        private int m_MaxHeight = 256;

        public FontTexture(int maxWidth = 256, int maxHeight = 256)
        {
            m_MaxWidth = maxWidth;
            m_MaxHeight = maxHeight;
        }

        private void CreateFontTex(bool isCheckNull = true)
        {
            if (isCheckNull)
            {
                if (m_FontTex != null)
                    return;
            }

            if (m_FontTex != null)
            {
                m_FontTex.Resize(m_MaxWidth, m_MaxHeight, TextureFormat.Alpha8, false);
            }
            else
            {
                m_FontTex = new Texture2D(m_MaxWidth, m_MaxHeight, TextureFormat.Alpha8, false, true);
            }
        }

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
