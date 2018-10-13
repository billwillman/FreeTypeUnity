using UnityEngine;
using System.Collections;
using FreeType;

public class fontTest : MonoBehaviour {

	void Start()
    {
        TextAsset asset = Resources.Load<TextAsset>("font/bmyh.ttf");
        if (asset != null)
        {
            FreeTypeBinder.Instance.CreateFontFromBuffer(asset.bytes, "本墨咏黑");
        }
    }
}
