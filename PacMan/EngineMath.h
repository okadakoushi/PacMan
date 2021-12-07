#pragma once

#include <cmath>

struct Vector2{
    //--function--//

    /// <summary>
    /// �R���X�g���N�^�B
    /// </summary>
    /// <param name="_x">x</param>
    /// <param name="_y">y</param>
    Vector2(const float _x = 0, const float _y = 0)
        : x(_x)
        , y(_y) 
    {
    }

    /// <summary>
    /// �x�N�g���̒������擾�B
    /// </summary>
    /// <returns></returns>
    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    /// <summary>
    /// 2�_�̋������擾�B
    /// </summary>
    /// <param name="vec"></param>
    /// <returns></returns>
    float Distance(const Vector2& vec) const
    {
        return std::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
    }

    /// <summary>
    /// ���ʃx�N�g�����擾�B
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
 
    //���@
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

    //���@
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

    //��@
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

    //���@
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

    //��r�B
    bool operator == (const Vector2& vec)
    {
        return (this->x == vec.x) && (this->y == vec.y);
    }

    //value//
    float x = 0;
    float y = 0;
};