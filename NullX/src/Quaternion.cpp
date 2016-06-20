/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
    {
    }

    Quaternion::Quaternion(const Quaternion& quat) : w(quat.w), x(quat.x), y(quat.y), z(quat.z)
    {
    }

    Quaternion::Quaternion(const float _x, const float _y, const float _z, const float angle) : w(cosf(angle / 2)), x(_x * sinf((angle / 2))), y(_y * sinf(angle / 2)), z(_z * sinf(angle / 2))
    {
    }

    Quaternion::Quaternion(const Vector3& vec, const float angle) : w(cosf(angle / 2)), x(vec.x * sinf(angle / 2)), y(vec.y * sinf(angle / 2)), z(vec.z * sinf(angle / 2))
    {
    }

    Quaternion::Quaternion(const Vector4& vec, const float angle) : w(cosf(angle / 2)), x(vec.x * sinf(angle / 2)), y(vec.y * sinf(angle / 2)), z(vec.z * sinf(angle / 2))
    {
    }

    void Quaternion::Normalize()
    {
        float mag = Magnitude(*this);
        w /= mag;
        x /= mag;
        y /= mag;
        z /= mag;
    }

    float Quaternion::Magnitude(const Quaternion& quat)
    {
        return sqrtf(MagnitudeSqr(quat));
    }

    float Quaternion::MagnitudeSqr(const Quaternion& quat)
    {
        return (quat.w * quat.w) + (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z);
    }

    float Quaternion::Dot(const Quaternion& quat1, const Quaternion& quat2)
    {
        return (quat1.w * quat2.w) + (quat1.x * quat2.x) + (quat1.y * quat2.y) + (quat1.z * quat2.z);
    }

    Quaternion Quaternion::Normalized(const Quaternion& quat)
    {
        Quaternion toReturn = Quaternion(quat);
        toReturn.Normalize();
        return toReturn;
    }

    Quaternion Quaternion::Conjugate(const Quaternion& quat)
    {
        Quaternion toReturn = Quaternion(quat);
        toReturn.x *= -1;
        toReturn.y *= -1;
        toReturn.z *= -1;
        return toReturn;
    }

    Quaternion Quaternion::Inverse(const Quaternion& quat)
    {
        return Conjugate(quat) / Magnitude(quat);
    }

    Vector3 Quaternion::ToEuler(const Quaternion& quat)
    {
        Vector3 toReturn = Vector3();
        float xSqr = quat.x * quat.x;
        float ySqr = quat.y * quat.y;
        float zSqr = quat.z * quat.z;

        toReturn.x = atan2f(2 * (quat.w * quat.x + quat.y * quat.z), 1 - (2 * (xSqr + ySqr)));
        toReturn.y = asinf(2 * (quat.w * quat.y - quat.z * quat.x));
        toReturn.z = atan2f(2 * (quat.w * quat.z + quat.x * quat.y), 1 - (2 * (ySqr + zSqr)));
       
        return toReturn;
    }

    Quaternion Quaternion::operator * (const Quaternion& quat)
    {
        Quaternion toReturn = Quaternion();
        toReturn.w = (w * quat.w) - (x * quat.x) - (y * quat.y) - (z * quat.z);
        toReturn.x = (w * quat.x) + (x * quat.w) + (y * quat.z) - (z * quat.y);
        toReturn.y = (w * quat.y) - (x * quat.z) + (y * quat.w) + (z * quat.x);
        toReturn.z = (w * quat.z) + (x * quat.y) - (y * quat.x) + (z * quat.w);
        
        return toReturn;
    }

    Quaternion Quaternion::operator * (const float num)
    {
        Quaternion toReturn = Quaternion(*this);
        toReturn.w *= num;
        toReturn.x *= num;
        toReturn.y *= num;
        toReturn.z *= num;

        return toReturn;
    }

    Quaternion Quaternion::operator / (const float num)
    {
        Quaternion toReturn = Quaternion(*this);
        toReturn.w /= num;
        toReturn.x /= num;
        toReturn.y /= num;
        toReturn.z /= num;

        return toReturn;
    }

    Quaternion Quaternion::operator *= (const Quaternion& quat)
    {
        w = (w * quat.w) - (x * quat.x) - (y * quat.y) - (z * quat.z);
        x = (w * quat.x) + (x * quat.w) + (y * quat.z) - (z * quat.y);
        y = (w * quat.y) - (x * quat.z) + (y * quat.w) + (z * quat.x);
        z = (w * quat.z) + (x * quat.y) - (y * quat.x) + (z * quat.w);

        return *this;
    }

    Quaternion Quaternion::operator *= (const float num)
    {
        w *= num;
        x *= num;
        y *= num;
        z *= num;

        return *this;
    }

    Quaternion Quaternion::operator /= (const float num)
    {
        w /= num;
        x /= num;
        y /= num;
        z /= num;

        return *this;
    }
}