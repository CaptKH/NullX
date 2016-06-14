/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>
#include <math.h>

namespace NullX
{
    Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
    Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
    Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
    Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
    Vector3 Vector3::backward = Vector3(0.0f, 0.0f, -1.0f);

    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {
    }

    Vector3::Vector3(const Vector3& vec) : x(vec.x), y(vec.y), z(vec.z)
    {
    }

    void Vector3::Normalize()
    {
        float mag = Magnitude(*this);
        x /= mag;
        y /= mag;
        z /= mag;
    }

    Vector3 Vector3::Normalized(const Vector3& vec)
    {
        Vector3 toReturn = Vector3(vec);
        toReturn.Normalize();
        return toReturn;
    }

    float Vector3::Magnitude(const Vector3& vec)
    {
        return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    }

    float Vector3::MagnitudeSqr(const Vector3& vec)
    {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }

    float Vector3::Dot(const Vector3& vec1, const Vector3& vec2)
    {
        return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    }

    float Vector3::Angle(Vector3& vec1, Vector3& vec2)
    {
        return acosf(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
    }

    float Vector3::Distance(Vector3& vec1, Vector3& vec2)
    {
        return Magnitude(vec1 - vec2);
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
        return Vector3((vec1.y * vec2.z) - (vec1.z * vec2.y), (vec1.z * vec2.x) - (vec1.x * vec2.z), (vec1.x * vec2.y) - (vec1.y * vec2.x));
    }

    bool Vector3::operator == (const Vector3& vec)
    {
        return (x == vec.x) ? (y == vec.y) ? (z == vec.z) ? true : false : false : false;
    }

    bool Vector3::operator != (const Vector3& vec)
    {
        return (x != vec.x) ? (y != vec.y) ? (z != vec.z)? true : false : false : false;
    }

    Vector3 Vector3::operator + (const Vector3& vec)
    {
        return Vector3(x + vec.x, y + vec.y, z + vec.z);
    }

    Vector3 Vector3::operator - (const Vector3& vec)
    {
        return Vector3(x - vec.x, y - vec.y, z - vec.z);
    }

    Vector3 Vector3::operator * (const float num)
    {
        return Vector3(x * num, y * num, z * num);
    }

    Vector3 Vector3::operator / (const float num)
    {
        return Vector3(x / num, y / num, z / num);
    }

    Vector3 Vector3::operator += (const Vector3& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    Vector3 Vector3::operator -= (const Vector3& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }

    Vector3 Vector3::operator *= (const float num)
    {
        x *= num;
        y *= num;
        z *= num;
        return *this;
    }

    Vector3 Vector3::operator /= (const float num)
    {
        x /= num;
        y /= num;
        z /= num;
        return *this;
    }
}