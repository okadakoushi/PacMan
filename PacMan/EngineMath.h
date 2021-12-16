#pragma once

#include <cmath>

struct Vector2
{
    //--function--//

    /// <summary>
    /// コンストラクタ。
    /// </summary>
    /// <param name="_x">x</param>
    /// <param name="_y">y</param>
    Vector2(const float _x = 0.0f, const float _y = 0.0f)
        : x(_x)
        , y(_y)
    {
    }

    /// <summary>
    /// ベクトルの長さを取得。
    /// </summary>
    /// <returns></returns>
    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    /// <summary>
    /// 2点の距離を取得。
    /// </summary>
    /// <param name="vec"></param>
    /// <returns></returns>
    float Distance(const Vector2& vec) const
    {
        return std::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
    }

    /// <summary>
    /// 方位ベクトルを取得。
    /// </summary>
    /// <returns></returns>
    Vector2 Normalized() const
    {
        if (x == 0 && y == 0) {
            return 0;
        }
        return{ x / Length() , y / Length() };
    }

    //--operator--//

    //加法
    Vector2 operator +(const Vector2& other) const
    {
        return{ x + other.x, y + other.y };
    }
    Vector2& operator +=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    //減法
    Vector2 operator -(const Vector2& other) const
    {
        return{ x - other.x, y - other.y };
    }
    Vector2& operator -=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    //乗法
    Vector2 operator *(float s) const
    {
        return{ x * s, y * s };
    }
    Vector2& operator *=(float s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    Vector2 operator *(Vector2 vec) const
    {
        return { x * vec.x, y * vec.y };
    }

    //除法
    Vector2 operator /(const float s) const
    {
        return{ x / s, y / s };
    }
    Vector2& operator /=(const float s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    //比較。
    bool operator == (const Vector2& vec)
    {
        //含みを持った等価。
        bool equalX = (fabsf(x - vec.x) <= FLT_EPSILON);
        bool equalY = (fabsf(y - vec.y) <= FLT_EPSILON);
        return equalX & equalY;
    }

    //value//
    float x = 0.0f;
    float y = 0.0f;
};

struct Vector2_Int
{
    //--function--//

    /// <summary>
    /// コンストラクタ。
    /// </summary>
    /// <param name="_x">x</param>
    /// <param name="_y">y</param>
    Vector2_Int(const int _x = 0.0f, const int _y = 0.0f)
        : x(_x)
        , y(_y)
    {
    }

    ///// <summary>
    ///// ベクトルの長さを取得。
    ///// </summary>
    ///// <returns></returns>
    //int Length() const
    //{
    //    return std::sqrt(x * x + y * y);
    //}

    ///// <summary>
    ///// 2点の距離を取得。
    ///// </summary>
    ///// <param name="vec"></param>
    ///// <returns></returns>
    //int Distance(const Vector2_Int& vec) const
    //{
    //    return std::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
    //}

    ///// <summary>
    ///// 方位ベクトルを取得。
    ///// </summary>
    ///// <returns></returns>
    //Vector2 Normalized() const
    //{
    //    if (x == 0 && y == 0) {
    //        return 0;
    //    }
    //    return{ x / Length() , y / Length() };
    //}

    //--operator--//

    //加法
    Vector2_Int operator +(const Vector2_Int& other) const
    {
        return{ x + other.x, y + other.y };
    }
    Vector2_Int& operator +=(const Vector2_Int& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    //減法
    Vector2_Int operator -(const Vector2_Int& other) const
    {
        return{ x - other.x, y - other.y };
    }
    Vector2_Int& operator -=(const Vector2_Int& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    //乗法
    Vector2_Int operator *(int s) const
    {
        return{ x * s, y * s };
    }
    Vector2 operator *(float s) const
    {
        return{ x * s, y * s };
    }
    Vector2_Int& operator *=(int s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    Vector2_Int operator *(Vector2_Int vec) const
    {
        return { x * vec.x, y * vec.y };
    }

    //除法
    Vector2_Int operator /(const int s) const
    {
        return{ x / s, y / s };
    }
    Vector2_Int& operator /=(const int s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    //比較。
    bool operator == (const Vector2_Int& vec)
    {
        return ((x == vec.x) & (y == vec.y));
    }

    //value//
    int x = 0;
    int y = 0;
};


namespace EngineMath
{
    static const Vector2_Int LEFT = { -1 , 0 };
    static const Vector2_Int UP = { 0 , -1 };
    static const Vector2_Int DOWN = { 0 , 1 };
    static const Vector2_Int RIGHT = { 1 , 0 };

    static inline Vector2_Int ConvertToIntVec(Vector2 vec)
    {
        return { (int)round(vec.x), (int)round(vec.y) };
    }

    static inline Vector2 CovertToFloatVec(Vector2_Int vec)
    {
        return { (float)vec.x,  (float)vec.y };
    }
};

