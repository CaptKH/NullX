/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 Vector3::Down = Vector3(0.0f, -1.0f, 0.0f);
    Vector3 Vector3::Left = Vector3(-1.0f, 0.0f, 0.0f);
    Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);
    Vector3 Vector3::Forward = Vector3(0.0f, 0.0f, 1.0f);
    Vector3 Vector3::Backward = Vector3(0.0f, 0.0f, -1.0f);

    Vector3::Vector3() : elementsSIMD(_mm_setzero_ps())
    {
    }

    Vector3::Vector3(float _x, float _y, float _z) : elementsSIMD(_mm_setr_ps(_x, _y, _z, 0.0f))
    {
    }

    Vector3::Vector3(__m128 vec) : elementsSIMD(vec)
    {
    }

    Vector3::Vector3(const Vector2& vec) : elementsSIMD(_mm_setr_ps(vec.x, vec.y, 0.0f, 0.0f))
    {
    }

    Vector3::Vector3(const Vector3& vec) : elementsSIMD(vec.elementsSIMD)
    {
    }

    Vector3::Vector3(const Vector4& vec) : elementsSIMD(_mm_setr_ps(vec.x, vec.y, vec.z, 0.0f))
    {
    }

    void Vector3::Normalize()
    {
        __m128 mag = _mm_set1_ps(Magnitude(*this));
        elementsSIMD = _mm_div_ps(elementsSIMD, mag);
    }

    float Vector3::Magnitude(const Vector3& vec)
    {
        return sqrtf(Dot(vec, vec));
    }

    float Vector3::MagnitudeSqr(const Vector3& vec)
    {
        return Dot(vec, vec);
    }

    float Vector3::Dot(const Vector3& vec1, const Vector3& vec2)
    {
        return _mm_dp_ps(vec1.elementsSIMD, vec2.elementsSIMD, 0x71).m128_f32[0];
    }

    float Vector3::Angle(Vector3& vec1, Vector3& vec2)
    {
        return acosf(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
    }

    float Vector3::Distance(Vector3& vec1, Vector3& vec2)
    {
        return Magnitude(vec1 - vec2);
    }

    Vector3 Vector3::Normalized(const Vector3& vec)
    {
        Vector3 toReturn = Vector3(vec);
        toReturn.Normalize();
        return toReturn;
    }

    Vector3 Vector3::Clamp(Vector3& vec, const float mag)
    {
        return Normalized(vec) *= mag;
    }

    Vector3 Vector3::Projection(Vector3& vec1, Vector3& vec2)
    {
        return vec2 * (Dot(vec1, vec2) / Magnitude(vec2));
    }

    Vector3 Vector3::Cross(const Vector3& vec1, const Vector3& vec2)
    {
        __m128 v1 = _mm_mul_ps(_mm_shuffle_ps(vec1.elementsSIMD, vec1.elementsSIMD, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(vec2.elementsSIMD, vec2.elementsSIMD, _MM_SHUFFLE(3, 1, 0, 2)));
        __m128 v2 = _mm_mul_ps(_mm_shuffle_ps(vec1.elementsSIMD, vec1.elementsSIMD, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(vec2.elementsSIMD, vec2.elementsSIMD, _MM_SHUFFLE(3, 0, 2, 1)));
        return Vector3(_mm_sub_ps(v1, v2));
    }

    Vector2 Vector3::ToVector2(const Vector3& vec)
    {
        return Vector2(vec.x, vec.y);
    }

    Vector4 Vector3::ToVector4(const Vector3& vec, const float w)
    {
        return Vector4(vec.x, vec.y, vec.z, w);
    }

    bool Vector3::operator == (const Vector3& vec)
    {
        __m128 compare = _mm_cmpeq_ps(elementsSIMD, vec.elementsSIMD);
        int mask = _mm_movemask_ps(compare);

        return (mask == 0xF) ? true : false;
    }

    bool Vector3::operator != (const Vector3& vec)
    {
        return !(*this == vec);
    }

    float Vector3::operator [] (const int num)
    {
        return elements[num];
    }

    Vector3 Vector3::operator + (const Vector3& vec)
    {
        return Vector3(_mm_add_ps(elementsSIMD, vec.elementsSIMD));
    }

    Vector3 Vector3::operator - (const Vector3& vec)
    {
        return Vector3(_mm_sub_ps(elementsSIMD, vec.elementsSIMD));
    }

    Vector3 Vector3::operator * (const float num)
    {
        __m128 mult = _mm_set1_ps(num);
        return Vector3(_mm_mul_ps(elementsSIMD, mult));
    }

    Vector3 Vector3::operator / (const float num)
    {
        __m128 div = _mm_set1_ps(num);
        return Vector3(_mm_div_ps(elementsSIMD, div));
    }

    Vector3 Vector3::operator += (const Vector3& vec)
    {
        *this = *this + vec;
        return *this;
    }

    Vector3 Vector3::operator -= (const Vector3& vec)
    {
        *this = *this - vec;
        return *this;
    }

    Vector3 Vector3::operator *= (const float num)
    {
        *this = *this * num;
        return *this;
    }

    Vector3 Vector3::operator /= (const float num)
    {
        *this = *this / num;
        return *this;
    }
}