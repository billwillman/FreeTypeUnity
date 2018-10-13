﻿/*
 * 单例
 */

using UnityEngine;
using System;
using System.Collections;
using Utils;


// 关于资源的类不允许使用单例
public class Singleton<T> where T : class, new()
{
    //
    // Static Fields
    //
    protected static T m_Instance;

    //
    // Static Properties
    //
    public static T Instance
    {
        get
        {
            if (m_Instance == null)
            {
                m_Instance = new T();
            }
            return m_Instance;
        }
    }

    //
    // Static Methods
    //
    public static T GetInstance()
    {
        return Instance;
    }
}