using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace FreeType {
    // FreeType字体管理
    public class FreeTypeBinder : MonoBehaviour {
        private IntPtr m_FreeTypePointer = default(IntPtr);
        // 字体管理MAP
        private Dictionary<FontType, IntPtr> m_FontsMap = new Dictionary<FontType, IntPtr>(FontTypeComparser.Default);
#if UNITY_STANDALONE_WIN || UNITY_EDITOR_WIN
        private const string FreeTypeDll = "freetype";
#elif UNITY_IOS
    private const string FreeTypeDll = "__Internal";
#endif

#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
        /*----------------------------Native API------------------------*/
        [DllImport(FreeTypeDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int FT_Init_FreeType(out IntPtr pointer);
        [DllImport(FreeTypeDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern void FT_Done_FreeType(IntPtr pointer);
        [DllImport(FreeTypeDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern void FT_Done_Face(IntPtr pointer);
        [DllImport(FreeTypeDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int FT_New_Memory_Face(IntPtr library, byte[] fontBuf, int fontSize, out IntPtr font);
        /*--------------------------------------------------------------*/
#endif

        private static int Init_FreeType(out IntPtr pointer) {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            int ret = FT_Init_FreeType(out pointer);
            return ret;
#endif
        }

        private static void Done_FreeType(IntPtr pointer) {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            FT_Done_FreeType(pointer);
#endif
        }

        private static void Done_Face(IntPtr pointer) {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            FT_Done_Face(pointer);
#endif
        }

        private static int New_Memory_Face(IntPtr library, byte[] fontBuf, int fontSize, out IntPtr font) {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            return FT_New_Memory_Face(library, fontBuf, fontSize, out font);
#endif
        }

        /*----------------------------------------------------------------*/

        private void Init() {
            var defaultValue = default(IntPtr);
            if (m_FreeTypePointer == defaultValue) {
                int ret = Init_FreeType(out m_FreeTypePointer);
                if (ret != 0)
                    throw new Exception("Could not init freetype library!");
            }
        }

        private void UnInit() {
            var defaultValue = default(IntPtr);
            if (m_FreeTypePointer != defaultValue) {
                Done_FreeType(m_FreeTypePointer);
                m_FreeTypePointer = defaultValue;
            }
        }

        // 释放字体库
        public void FreeFont(string fontName, int fontSize = 0) {
            IntPtr pointer;
            FontType key = new FontType();
            key.fontName = fontName;
            key.fontSize = fontSize;
            if (m_FontsMap.TryGetValue(key, out pointer)) {
                if (pointer != default(IntPtr)) {
                    Done_Face(pointer);
                }
                m_FontsMap.Remove(key);
            }
        }

        public IntPtr FindFont(string fontName, int fontSize = 0) {
            FontType key = new FontType();
            key.fontName = fontName;
            key.fontSize = fontSize;
            IntPtr ret;
            if (!m_FontsMap.TryGetValue(key, out ret))
                ret = default(IntPtr);
            return ret;
        }

        /// <summary>
        /// 创建字体如果能找到则直接返回
        /// </summary>
        /// <param name="fileName">字体TTF文件路径</param>
        /// <param name="fontName">字体名</param>
        /// <param name="fontSize">字体大小</param>
        /// <returns></returns>
        public IntPtr CreateFontFromBuffer(byte[] buffer, string fontName, int fontSize = 0) {
            IntPtr ret = FindFont(fontName, fontSize);
            var defaultPrt = default(IntPtr);
            if (ret != defaultPrt)
                return ret;
            if (buffer == null || buffer.Length <= 0)
                return defaultPrt;
            int err = New_Memory_Face(m_FreeTypePointer, buffer, fontSize, out ret);
            if (err != 0)
                throw new Exception("Could not open font");

            FontType key = new FontType();
            key.fontName = fontName;
            key.fontSize = fontSize;
            m_FontsMap[key] = ret;

            return ret;
        }

        public void ClearAllFonts() {
            var defaultPtr = default(IntPtr);
            var iter = m_FontsMap.GetEnumerator();
            while (iter.MoveNext()) {
                var fontPtr = iter.Current.Value;
                if (fontPtr != defaultPtr)
                    Done_Face(fontPtr);
            }
            iter.Dispose();
            m_FontsMap.Clear();
        }

        /*-------------------------------------------------------------*/

        void Awake() {
            Init();
        }

        void OnDestroy() {
            // 删除缓存字体
            ClearAllFonts();
            UnInit();
        }
    }

}
