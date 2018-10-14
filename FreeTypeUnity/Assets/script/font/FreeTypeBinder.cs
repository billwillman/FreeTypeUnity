using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace FreeType {
    // FreeType字体管理
    public class FreeTypeBinder : MonoBehaviour {

        private static FreeTypeBinder m_Instance = null;

        public static FreeTypeBinder Instance
        {
            get
            {
                if (m_Instance == null)
                {
                    GameObject obj = new GameObject("FontMgr", typeof(FreeTypeBinder));
                    m_Instance = obj.GetComponent<FreeTypeBinder>();
                }
                return m_Instance;
            }
        }

        public static FreeTypeBinder GetInstance()
        {
            return Instance;
        }

        private IntPtr m_FreeTypePointer = default(IntPtr);
        // 字体管理MAP
        private Dictionary<FontType, FreeTypeFont> m_FontsMap = new Dictionary<FontType, FreeTypeFont>(FontTypeComparser.Default);
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
        private static extern int FT_New_Memory_Face(IntPtr library, [MarshalAs(UnmanagedType.LPArray)]byte[] fontBuf,
            [MarshalAs(UnmanagedType.U4)]uint byteSize, [MarshalAs(UnmanagedType.U4)]uint faceIndex, out IntPtr font);
        [DllImport(FreeTypeDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int FT_Set_Char_Size(IntPtr font, [MarshalAs(UnmanagedType.I4)]int char_width, [MarshalAs(UnmanagedType.I4)] int char_height,
            [MarshalAs(UnmanagedType.U4)]uint horz_resolution, [MarshalAs(UnmanagedType.U4)]uint vert_resolution );
        [DllImport(FreeTypeDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int FT_Set_Pixel_Sizes(IntPtr font, [MarshalAs(UnmanagedType.U4)]uint pixel_width,
            [MarshalAs(UnmanagedType.U4)]uint pixel_height);
        /*--------------------------------------------------------------*/
#endif

        private static int Init_FreeType(out IntPtr pointer) {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            int ret = FT_Init_FreeType(out pointer);
            return ret;
#endif
        }

        private int Set_Char_Size(IntPtr font, int char_width, int char_height, uint horz_resolution, uint vert_resolution)
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            int ret = FT_Set_Char_Size(font, char_width, char_height, horz_resolution, vert_resolution);
            return ret;
#endif
        }

        private int Set_Pixel_Sizes(IntPtr font, uint pixel_widht, uint pixel_height)
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            int ret = FT_Set_Pixel_Sizes(font, pixel_widht, pixel_height);
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

        private static int New_Memory_Face(IntPtr library, byte[] fontBuf, uint faceIndex, out IntPtr font)
        {
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN || UNITY_IOS
            return FT_New_Memory_Face(library, fontBuf, (uint)fontBuf.Length, faceIndex, out font);
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
        public void FreeFont(string fontName, uint faceIndex = 0) {
            FreeTypeFont font;
            FontType key = new FontType();
            key.fontName = fontName;
            key.faceIndex = faceIndex;
            if (m_FontsMap.TryGetValue(key, out font))
            {
                if (font != null && font.font != default(IntPtr))
                {
                    Done_Face(font.font);
                }
                m_FontsMap.Remove(key);
            }
        }

        public IntPtr FindFont(string fontName, uint faceIndex = 0)
        {
            FontType key = new FontType();
            key.fontName = fontName;
            key.faceIndex = faceIndex;
            FreeTypeFont ret;
            if (!m_FontsMap.TryGetValue(key, out ret))
               return default(IntPtr);
            if (ret == null)
                return default(IntPtr); 
            return ret.font;
        }

        /// <summary>
        /// 创建字体如果能找到则直接返回
        /// </summary>
        /// <param name="fileName">字体TTF文件路径</param>
        /// <param name="fontName">字体名</param>
        /// <param name="fontSize">字体大小</param>
        /// <returns></returns>
        public IntPtr CreateFontFromBuffer(byte[] buffer, string fontName, uint faceIndex = 0)
        {
            IntPtr ret = FindFont(fontName, faceIndex);
            var defaultPrt = default(IntPtr);
            if (ret != defaultPrt)
                return ret;
            if (buffer == null || buffer.Length <= 0)
                return defaultPrt;
            int err = New_Memory_Face(m_FreeTypePointer, buffer, faceIndex, out ret);
            if (err != 0)
                throw new Exception(string.Format("Could not open font: errCode {0:D}", err));

            FontType key = new FontType();
            key.fontName = fontName;
            key.faceIndex = faceIndex;
            FreeTypeFont font = new FreeTypeFont();
            font.font = ret;
            m_FontsMap[key] = font;
            ApplyFont(font);
            return ret;
        }

        private void ApplyFont(FreeTypeFont font)
        {
            if (font == null || font.font == default(IntPtr))
                return;
            int ret = -1;
            if (font.sizeType == FreeTypeSizeType.useDPI)
            {
                ret = Set_Char_Size(font.font, 0, (int)font.currentSize, font.hDpi, font.vDpi);
                
            } else if (font.sizeType == FreeTypeSizeType.usePixel)
            {
                ret = Set_Pixel_Sizes(font.font, 0, font.currentSize);
            }
            if (ret != 0)
                throw new Exception("ApplyFont Error!");
        }

        public void ClearAllFonts() {
            var defaultPtr = default(IntPtr);
            var iter = m_FontsMap.GetEnumerator();
            while (iter.MoveNext()) {
                var font = iter.Current.Value;
                if (font != null && font.font != defaultPtr)
                    Done_Face(font.font);
            }
            iter.Dispose();
            m_FontsMap.Clear();
        }

        /*-------------------------------------------------------------*/

        void Awake() {
            m_Instance = this;
            Init();
        }

        void OnDestroy() {
            // 删除缓存字体
            ClearAllFonts();
            UnInit();

            m_Instance = null;
        }
    }

}
