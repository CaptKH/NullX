/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    Vector4 Vector4::Up       = Vector4( 0.0f,  1.0f,  0.0f, 0.0f);
    Vector4 Vector4::Down     = Vector4( 0.0f, -1.0f,  0.0f, 0.0f);
    Vector4 Vector4::Left     = Vector4(-1.0f,  0.0f,  0.0f, 0.0f);
    Vector4 Vector4::Right    = Vector4( 1.0f,  0.0f,  0.0f, 0.0f);
    Vector4 Vector4::Forward  = Vector4( 0.0f,  0.0f,  1.0f, 0.0f);
    Vector4 Vector4::Backward = Vector4( 0.0f,  0.0f, -1.0f, 0.0f);

    Vector4::Vector4() : elementsSIMD(_mm_setzero_ps())
    {
    }

    Vector4::Vector4(float _x, float _y, float _z, float _w) : elementsSIMD(_mm_setr_ps(_x, _y, _z, _w))
    {
    }
    
    Vector4::Vector4(__m128 vec, const float _w) : elementsSIMD(vec), w(_w)
    {
    }

    Vector4::Vector4(const Vector2& vec, const float _w) : elementsSIMD(_mm_setr_ps(vec.x, vec.y, 0.0f, _w))
    {
    }

    Vector4::Vector4(const Vector3& vec, const float _w) : elementsSIMD(_mm_setr_ps(vec.x, vec.y, vec.z, _w))
    {
    }

    Vector4::Vector4(const Vector4& vec) : elementsSIMD(vec.elementsSIMD)
    {
    }

    void Vector4::Normalize()
    {
        float mag = Magnitude(*this);
        __m128 magVec = _mm_setr_ps(mag, mag, mag, 1.0f);
        elementsSIMD = _mm_div_ps(elementsSIMD, magVec);
    }

    float Vector4::Magnitude(const Vector4& vec)
    {
        return sqrtf(Dot(vec, vec));
    }

    float Vector4::MagnitudeSqr(const Vector4& vec)
    {
        return Dot(vec, vec);
    }

    float Vector4::Dot(const Vector4& vec1, const Vector4& vec2)
    {
        return _mm_dp_ps(vec1.elementsSIMD, vec2.elementsSIMD, 0x71).m128_f32[0];
    }

    float Vector4::Angle(Vector4& vec1, Vector4& vec2)
    {
        return acosf(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
    }

    float Vector4::Distance(Vector4& vec1, Vector4& vec2)
    {
        return Magnitude(vec1 - vec2);
    }

    Vector4 Vector4::Normalized(const Vector4& vec)
    {
        Vector4 toReturn = Vector4(vec);
        toReturn.Normalize();
        return toReturn;
    }

    Vector4 Vector4::Clamp(Vector4& vec, const float mag)
    {
        return Normalized(vec) *= mag;
    }

    Vector4 Vector4::Projection(Vector4& vec1, Vector4& vec2)
    {
        return vec2 * (Dot(vec1, vec2) / Magnitude(vec2));
    }
    
    Vector2 Vector4::ToVector2(const Vector4& vec)
    {
        return Vector2(vec.x, vec.y);
    }

    Vector3 Vector4::ToVector3(const Vector4& vec)
    {
        return Vector3(vec.x, vec.y, vec.z);
    }

    Vector4 Vector4::Cross(const Vector4& vec1, const Vector4& vec2)
    {
        __m128 v1 = _mm_mul_ps(_mm_shuffle_ps(vec1.elementsSIMD, vec1.elementsSIMD, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(vec2.elementsSIMD, vec2.elementsSIMD, _MM_SHUFFLE(3, 1, 0, 2)));
        __m128 v2 = _mm_mul_ps(_mm_shuffle_ps(vec1.elementsSIMD, vec1.elementsSIMD, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(vec2.elementsSIMD, vec2.elementsSIMD, _MM_SHUFFLE(3, 0, 2, 1)));
        return Vector4(_mm_sub_ps(v1, v2), 0.0f);
    }

    bool Vector4::operator == (const Vector4& vec)
    {
        __m128 compare = _mm_cmpeq_ps(elementsSIMD, vec.elementsSIMD);
        int mask = _mm_movemask_ps(compare);

        return (mask == 0xF) ? true : false;
    }

    bool Vector4::operator != (const Vector4& vec)
    {
        return !(*this == vec);
    }

    float& Vector4::operator [] (const int num)
    {
        return elements[num];
    }

    Vector4 Vector4::operator + (const Vector4& vec)
    {
        return Vector4(_mm_add_ps(elementsSIMD, vec.elementsSIMD), w);
    }

    Vector4 Vector4::operator - (const Vector4& vec)
    {
        return Vector4(_mm_sub_ps(elementsSIMD, vec.elementsSIMD), w);
    }

    Vector4 Vector4::operator * (const float num)
    {
        __m128 mult = _mm_set1_ps(num);
        return Vector4(_mm_mul_ps(elementsSIMD, mult), w);
    }

    Vector4 Vector4::operator / (const float num)
    {
        __m128 div = _mm_set1_ps(num);
        return Vector4(_mm_mul_ps(elementsSIMD, div), w);
    }

    Vector4 Vector4::operator += (const Vector4& vec)
    {
        *this = *this + vec;
        return *this;
    }

    Vector4 Vector4::operator -= (const Vector4& vec)
    {
        *this = *this - vec;
        return *this;
    }

    Vector4 Vector4::operator *= (const float num)
    {
        *this = *this * num;
        return *this;
    }

    Vector4 Vector4::operator /= (const float num)
    {
        *this = *this / num;
        return *this;
    }
}