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

    Vector2::Vector2() : x(0.0f), y(0.0f)
    {
    }

    Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
    {
    }

    Vector2::Vector2(const Vector2& vec) : x(vec.x), y(vec.y)
    {
    }

    Vector2::Vector2(const Vector3& vec) : x(vec.x), y(vec.y)
    {
    }

    Vector2::Vector2(const Vector4& vec) : x(vec.x), y(vec.y)
    {
    }

    void Vector2::Normalize()
    {
        float mag = Magnitude(*this);
        x /= mag;
        y /= mag;
    }

    float Vector2::Magnitude(const Vector2& vec)
    {
        return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
    }

    float Vector2::MagnitudeSqr(const Vector2& vec)
    {
        return (vec.x * vec.x) + (vec.y * vec.y);
    }

    float Vector2::Dot(const Vector2& vec1, const Vector2& vec2)
    {
        return (vec1.x * vec2.x) + (vec1.y * vec2.y);
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
        return Normalized(vec) *= mag;
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
        return (x == vec.x) ? (y == vec.y) ? true : false : false;
    }

    bool Vector2::operator != (const Vector2& vec)
    {
        return (x != vec.x) ? (y != vec.y) ? true : false : false;
    }

    float Vector2::operator [] (const int num)
    {
        return elements[num];
    }

    Vector2 Vector2::operator + (const Vector2& vec)
    {
        return Vector2(x + vec.x, y + vec.y);
    }

    Vector2 Vector2::operator - (const Vector2& vec)
    {
        return Vector2(x - vec.x, y - vec.y);
    }

    Vector2 Vector2::operator * (const float num)
    {
        return Vector2(x * num, y * num);
    }

    Vector2 Vector2::operator / (const float num)
    {
        return Vector2(x / num, y / num);
    }

    Vector2 Vector2::operator += (const Vector2& vec)
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    Vector2 Vector2::operator -= (const Vector2& vec)
    {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }

    Vector2 Vector2::operator *= (const float num)
    {
        x *= num;
        y *= num;
        return *this;
    }

    Vector2 Vector2::operator /= (const float num)
    {
        x /= num;
        y /= num;
        return *this;
    }
}