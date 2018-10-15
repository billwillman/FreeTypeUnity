using System;
using Utils;
using System.Runtime.InteropServices;

namespace FreeType {

    public enum FreeTypeSizeType
    {
        useDPI,
        usePixel
    }

    // 字体信息
    public class FreeTypeFont
    {
        // 水平垂直DPI
        public uint hDpi = 72;
        public uint vDpi = 72;

        public FreeTypeSizeType sizeType = FreeTypeSizeType.usePixel;
        public IntPtr font;
        // 当前大小
        public uint currentSize = 16;
        
    }

    public class FontTypeComparser : StructComparser<FontType> { }

    public struct FontType: IEquatable<FontType> {
        public string fontName;
        public uint faceIndex;

        public bool Equals(FontType other) {
            return this == other;
        }

        public static bool operator ==(FontType a, FontType b) {
            return (a.faceIndex == b.faceIndex) && (string.Compare(a.fontName, b.fontName) == 0);
        }

        public static bool operator !=(FontType a, FontType b) {
            return !(a == b);
        }

        public override bool Equals(object obj) {
            if (obj == null)
                return false;

            if (GetType() != obj.GetType())
                return false;

            if (obj is FontType) {
                FontType other = (FontType)obj;
                return Equals(other);
            } else
                return false;

        }

        public override int GetHashCode() {
            int ret = FilePathMgr.InitHashValue();
            FilePathMgr.HashCode(ref ret, fontName);
            FilePathMgr.HashCode(ref ret, faceIndex);
            return ret;
        }
    }

    public class FontRectKey : IEquatable<FontRectKey>
    {
        public char value;
        // 字体名
        public string fontName;
        // 字体Face
        public uint faceIndex;
        // 字体大小
        public uint fontSize;
        // 字体大小类型
        public FreeTypeSizeType fontSizeType;
        // H DPI
        public uint hDpi;
        // V DPI
        public uint vDpi;

        public bool Equals(FontRectKey other)
        {
            return this == other;
        }

        public static bool operator ==(FontRectKey a, FontRectKey b)
        {
            return (a.faceIndex == b.faceIndex) &&
                    (a.value == b.value) && (a.fontSize == b.fontSize) && (a.fontSizeType == b.fontSizeType) &&
                    (a.hDpi == b.hDpi) && (a.vDpi == b.vDpi) && (string.Compare(a.fontName, b.fontName) == 0);
        }

        public static bool operator !=(FontType a, FontType b)
        {
            return !(a == b);
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (GetType() != obj.GetType())
                return false;

            if (obj is FontRectKey)
            {
                FontRectKey other = (FontRectKey)obj;
                return Equals(other);
            }
            else
                return false;

        }

        public override int GetHashCode()
        {
            int ret = FilePathMgr.InitHashValue();
            FilePathMgr.HashCode(ref ret, value);
            FilePathMgr.HashCode(ref ret, faceIndex);
            FilePathMgr.HashCode(ref ret, fontName);
            FilePathMgr.HashCode(ref ret, fontSize);
            FilePathMgr.HashCode(ref ret, fontSizeType);
            FilePathMgr.HashCode(ref ret, hDpi);
            FilePathMgr.HashCode(ref ret, vDpi);
            return ret;
        }

    }
}
