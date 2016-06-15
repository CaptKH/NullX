/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    Vector4 Vector4::Up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4 Vector4::Down = Vector4(0.0f, -1.0f, 0.0f, 0.0f);
    Vector4 Vector4::Left = Vector4(-1.0f, 0.0f, 0.0f, 0.0f);
    Vector4 Vector4::Right = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4 Vector4::Forward = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4 Vector4::Backward = Vector4(0.0f, 0.0f, -1.0f, 0.0f);

    Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
    }

    Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
    {
    }

    Vector4::Vector4(const Vector4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w)
    {
    }

    void Vector4::Normalize()
    {
        float mag = Magnitude(*this);
        x /= mag;
        y /= mag;
        z /= mag;
    }

    Vector4 Vector4::Normalized(const Vector4& vec)
    {
        Vector4 toReturn = Vector4(vec);
        toReturn.Normalize();
        return toReturn;
    }

    float Vector4::Magnitude(const Vector4& vec)
    {
        return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    }

    float Vector4::MagnitudeSqr(const Vector4& vec)
    {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }

    float Vector4::Dot(const Vector4& vec1, const Vector4& vec2)
    {
        return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    }

    float Vector4::Angle(Vector4& vec1, Vector4& vec2)
    {
        return acosf(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
    }

    float Vector4::Distance(Vector4& vec1, Vector4& vec2)
    {
        return Magnitude(vec1 - vec2);
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
        return Vector4((vec1.y * vec2.z) - (vec1.z * vec2.y), (vec1.z * vec2.x) - (vec1.x * vec2.z), (vec1.x * vec2.y) - (vec1.y * vec2.x), 0.0f);
    }

    bool Vector4::operator == (const Vector4& vec)
    {
        return (x == vec.x) ? (y == vec.y) ? (z == vec.z) ? true : false : false : false;
    }

    bool Vector4::operator != (const Vector4& vec)
    {
        return (x != vec.x) ? (y != vec.y) ? (z != vec.z) ? true : false : false : false;
    }

    float& Vector4::operator [] (const int num)
    {
        return elements[num];
    }

    Vector4 Vector4::operator + (const Vector4& vec)
    {
        return Vector4(x + vec.x, y + vec.y, z + vec.z, w);
    }

    Vector4 Vector4::operator - (const Vector4& vec)
    {
        return Vector4(x - vec.x, y - vec.y, z - vec.z, w);
    }

    Vector4 Vector4::operator * (const float num)
    {
        return Vector4(x * num, y * num, z * num, w);
    }

    Vector4 Vector4::operator / (const float num)
    {
        return Vector4(x / num, y / num, z / num, w);
    }

    Vector4 Vector4::operator += (const Vector4& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    Vector4 Vector4::operator -= (const Vector4& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }

    Vector4 Vector4::operator *= (const float num)
    {
        x *= num;
        y *= num;
        z *= num;
        return *this;
    }

    Vector4 Vector4::operator /= (const float num)
    {
        x /= num;
        y /= num;
        z /= num;
        return *this;
    }
}