using System;
using UnityEngine;
using System.Collections;
using FreeType;

public class rectTest : MonoBehaviour {
    private FontRectCombine m_Combine = new FontRectCombine(256, 256);
    void OnGUI()
    {
        if (GUILayout.Button("添加随机区域框"))
        {
            byte v = (byte)(m_Combine.NodeCount + 33);
            char value = Convert.ToChar(v);
            //var font = FreeTypeBinder.GetInstance().FindFreeTypeFont("本墨咏黑");
            int w = UnityEngine.Random.Range(10, 50);
            m_Combine.InsertNode(value, 16, FreeTypeSizeType.usePixel, 72, 72, w, w);
        }

        if (m_Combine != null)
        {
            m_Combine.ForEachBTree(OnGUI_DrawNode);
        }
    }

    void OnGUI_DrawNode(BTreeNode<FontRectKey> node)
    {
        if (node == null)
            return;
        int left = 200;
        int top = 0;
        GUI.Button(new Rect(left + node.x, top + node.y, node.virtualPic.width, node.virtualPic.height), node.virtualPic.key.value.ToString());
    }

    void OnDestroy()
    {
        if (m_Combine != null)
        {
            m_Combine.OnDestroy();
            m_Combine = null;
        }
    }
}
