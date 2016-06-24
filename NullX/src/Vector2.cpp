/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    Vector2 Vector2::Up    = Vector2( 0.0f,  1.0f);
    Vector2 Vector2::Down  = Vector2( 0.0f, -1.0f);
    Vector2 Vector2::Left  = Vector2(-1.0f,  0.0f);
    Vector2 Vector2::Right = Vector2( 1.0f,  0.0f);

    Vector2::Vector2() : elementsSIMD(_mm_setzero_ps())
    {
    }

    Vector2::Vector2(__m128 vec) : elementsSIMD(vec)
    {
    }

    Vector2::Vector2(float _x, float _y) : elementsSIMD(_mm_setr_ps(_x, _y, 0.0f, 0.0f))
    {
    }

    Vector2::Vector2(const Vector2& vec) : elementsSIMD(vec.elementsSIMD)
    {
    }

    Vector2::Vector2(const Vector3& vec) : elementsSIMD(_mm_setr_ps(vec.x, vec.y, 0.0f, 0.0f))
    {
    }

    Vector2::Vector2(const Vector4& vec) : elementsSIMD(_mm_setr_ps(vec.x, vec.y, 0.0f, 0.0f))
    {
    }

    void Vector2::Normalize()
    {
        __m128 mag = _mm_set1_ps(Magnitude(*this));
        elementsSIMD = _mm_div_ps(elementsSIMD, mag);
    }

    float Vector2::Magnitude(const Vector2& vec)
    {
        return sqrtf(Dot(vec, vec));
    }

    float Vector2::MagnitudeSqr(const Vector2& vec)
    {
        return Dot(vec, vec);
    }

    float Vector2::Dot(const Vector2& vec1, const Vector2& vec2)
    {
        return _mm_dp_ps(vec1.elementsSIMD, vec2.elementsSIMD, 0x31).m128_f32[0];
    }

    float Vector2::Angle(Vector2& vec1, Vector2& vec2)
    {
        return acosf(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
    }

    float Vector2::Distance(Vector2& vec1, Vector2& vec2)
    {
        return Magnitude(vec1 - vec2);
    }

    Vector2 Vector2::Normalized(const Vector2& vec)
    {
        Vector2 toReturn = Vector2(vec);
        toReturn.Normalize();
        return toReturn;
    }

    Vector2 Vector2::Clamp(Vector2& vec, const float mag)
    {
        if(Magnitude(vec) > mag)
            return Normalized(vec) *= mag;
        
        return vec;
    }

    Vector2 Vector2::Projection(Vector2& vec1, Vector2& vec2)
    {
        return vec2 * (Dot(vec1, vec2) / Magnitude(vec2));
    }

    Vector3 Vector2::ToVector3(const Vector2& vec)
    {
        return Vector3(vec.x, vec.y, 0.0f);
    }

    Vector4 Vector2::ToVector4(const Vector2& vec, const float w)
    {
        return Vector4(vec.x, vec.y, 0.0f, w);
    }

    bool Vector2::operator == (const Vector2& vec)
    {
        __m128 compare = _mm_cmpeq_ps(elementsSIMD, vec.elementsSIMD);
        int mask = _mm_movemask_ps(compare);

        return (mask == 0xF) ? true : false;
    }

    bool Vector2::operator != (const Vector2& vec)
    {
        return !(*this == vec);
    }

    float Vector2::operator [] (const int num)
    {
        return elements[num];
    }

    Vector2 Vector2::operator + (const Vector2& vec)
    {
        return Vector2(_mm_add_ps(elementsSIMD, vec.elementsSIMD));
    }

    Vector2 Vector2::operator - (const Vector2& vec)
    {
        return Vector2(_mm_sub_ps(elementsSIMD, vec.elementsSIMD));
    }

    Vector2 Vector2::operator * (const float num)
    {
        __m128 mult = _mm_set1_ps(num);
        return Vector2(_mm_mul_ps(elementsSIMD, mult));
    }

    Vector2 Vector2::operator / (const float num)
    {
        __m128 div = _mm_set1_ps(num);
        return Vector2(_mm_div_ps(elementsSIMD, div));
    }

    Vector2 Vector2::operator += (const Vector2& vec)
    {
        *this = *this + vec;
        return *this;
    }

    Vector2 Vector2::operator -= (const Vector2& vec)
    {
        *this = *this - vec;
        return *this;
    }

    Vector2 Vector2::operator *= (const float num)
    {
        *this = *this * num;
        return *this;
    }

    Vector2 Vector2::operator /= (const float num)
    {
        *this = *this / num;
        return *this;
    }
}