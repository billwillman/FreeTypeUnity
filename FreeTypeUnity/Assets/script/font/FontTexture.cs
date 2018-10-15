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

        public void OnDestroy()
        {
            DestroyFontTex();
        }
    }
}
