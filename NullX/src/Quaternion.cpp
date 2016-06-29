/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    Quaternion::Quaternion() : elementsSIMD(_mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f))
    {
    }

    Quaternion::Quaternion(const Quaternion& quat) : elementsSIMD(_mm_setr_ps(quat.w, quat.x, quat.y, quat.z))
    {
    }

    Quaternion::Quaternion(const Vector3& vec, const float angle) : elementsSIMD(_mm_setr_ps(cosf(angle / 2), vec.x * sinf((angle / 2)), vec.y * sinf(angle / 2), vec.z * sinf(angle / 2)))
    {
        Vector3 vecNorm = Vector3::Normalized(vec);
        float sinAng = sinf(angle / 2);
        elementsSIMD = _mm_setr_ps(1, vecNorm.x, vecNorm.y, vecNorm.z);
        elementsSIMD = _mm_mul_ps(elementsSIMD, _mm_setr_ps(cosf(angle / 2), sinAng, sinAng, sinAng));
    }

    void Quaternion::Normalize()
    {
        __m128 magVec = _mm_set1_ps(Magnitude(*this));
        elementsSIMD = _mm_div_ps(elementsSIMD, magVec);
    }

    float Quaternion::Magnitude(const Quaternion& quat)
    {
        return sqrtf(Dot(quat, quat));
    }

    float Quaternion::MagnitudeSqr(const Quaternion& quat)
    {
        return Dot(quat, quat);
    }

    float Quaternion::Dot(const Quaternion& quat1, const Quaternion& quat2)
    {
        return  _mm_dp_ps(quat1.elementsSIMD, quat2.elementsSIMD, 0xF1).m128_f32[0];
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
        __m128 neg = _mm_setr_ps(1, -1, -1, -1);
        toReturn.elementsSIMD = _mm_mul_ps(toReturn.elementsSIMD, neg);
        return toReturn;
    }

    Quaternion Quaternion::Inverse(const Quaternion& quat)
    {
        return Conjugate(quat) / Magnitude(quat);
    }

    Vector3 Quaternion::ToEuler(const Quaternion& quat)
    {
        // Shout out to euclideanspace.com for the formulas
        Vector3 toReturn = Vector3();
        float* elementsSqr = _mm_mul_ps(quat.elementsSIMD, quat.elementsSIMD).m128_f32;
        float xSqr = elementsSqr[1];
        float ySqr = elementsSqr[2];
        float zSqr = elementsSqr[3];


        toReturn.x = atan2f(2 * (quat.x * quat.w - quat.y * quat.z), 1 - (2 * (xSqr + ySqr)));
        toReturn.y = asinf(2 * (quat.w * quat.y + quat.x * quat.z));
        toReturn.z = atan2f(2 * (quat.w * quat.z - quat.x * quat.y), 1 - (2 * (ySqr + zSqr)));
        
        return toReturn;
    }

    Quaternion Quaternion::operator * (const Quaternion& quat)
    {
        Quaternion toReturn = Quaternion();
        __m128 mask1 = _mm_mul_ps(_mm_set1_ps(w), _mm_setr_ps(quat.w, quat.x, quat.y, quat.z));
        __m128 mask2 = _mm_mul_ps(_mm_set1_ps(x), _mm_setr_ps(-quat.x, quat.w, -quat.z, quat.y));
        __m128 mask3 = _mm_mul_ps(_mm_set1_ps(y), _mm_setr_ps(-quat.y, quat.z, quat.w, -quat.x));
        __m128 mask4 = _mm_mul_ps(_mm_set1_ps(z), _mm_setr_ps(-quat.z, -quat.y, quat.x, quat.w));

        /* toReturn.w = (w * quat.w) - (x * quat.x) - (y * quat.y) - (z * quat.z);
           toReturn.x = (w * quat.x) + (x * quat.w) + (y * quat.z) - (z * quat.y);
           toReturn.y = (w * quat.y) - (x * quat.z) + (y * quat.w) + (z * quat.x);
           toReturn.z = (w * quat.z) + (x * quat.y) - (y * quat.x) + (z * quat.w); */
        toReturn.elementsSIMD = _mm_add_ps(_mm_add_ps(mask1, mask2), _mm_add_ps(mask3, mask4));

        return toReturn;
    }

    Quaternion Quaternion::operator * (const float num)
    {
        Quaternion toReturn = Quaternion(*this);
        toReturn.elementsSIMD = _mm_mul_ps(elementsSIMD, _mm_set1_ps(num));
        return toReturn;
    }

    Quaternion Quaternion::operator / (const float num)
    {
        Quaternion toReturn = Quaternion(*this);
        toReturn.elementsSIMD = _mm_div_ps(elementsSIMD, _mm_set1_ps(num));
        return toReturn;
    }

    Quaternion Quaternion::operator *= (const Quaternion& quat)
    {
        *this = *this * quat;
        return *this;
    }

    Quaternion Quaternion::operator *= (const float num)
    {
        *this = *this * num;
        return *this;
    }

    Quaternion Quaternion::operator /= (const float num)
    {
        *this = *this / num;
        return *this;
    }
}