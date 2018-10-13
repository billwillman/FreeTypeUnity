using System;
using Utils;

namespace FreeType {

    public class FontTypeComparser : StructComparser<FontType> { }

    public struct FontType: IEquatable<FontType> {
        public string fontName;
        public int fontSize;

        public bool Equals(FontType other) {
            return this == other;
        }

        public static bool operator ==(FontType a, FontType b) {
            return (a.fontSize == b.fontSize) && (string.Compare(a.fontName, b.fontName) == 0);
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
            FilePathMgr.HashCode(ref ret, fontSize);
            return ret;
        }
    }
}
