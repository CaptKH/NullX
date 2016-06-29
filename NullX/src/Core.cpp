/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

namespace NullX
{
    float PowRecursive(float num, int pow, float base)
    {
        return (pow > 0) ?
            (pow >  1) ? PowRecursive(num * base, pow - 1, base) : num :
            (pow < -1) ? PowRecursive(num * base, pow + 1, base) : 1 / num;
    }

    constexpr float Pow(const float num, const int pow)
    {
        return (pow == 0) ? 1.0f : PowRecursive(num, pow, num);
    }

    constexpr float Exp(const int pow)
    {
        return Pow(e, pow);
    }

    constexpr float Abs(const float x)
    {
        return (x < 0) ? x * -1 : x;
    }

    constexpr float Min(const float x, const float y)
    {
        return (x < y) ? x : y;
    }

    constexpr float Max(const float x, const float y)
    {
        return (x > y) ? x : y;
    }

    constexpr float Clamp(const float num, const float min, const float max)
    {
        return (num < min) ? min : (num > max) ? max : num;
    }

    constexpr float Floor(const float num)
    {
        return (num < 0) ? static_cast<int>(num) - 1 : static_cast<int>(num);
    }

    constexpr float Ceiling(const float num)
    {
        return (num < 0) ? static_cast<int>(num) : (num == 0) ? num : static_cast<int>(num) + 1;
    }

    constexpr float Round(const float num)
    {
        return (num - Floor(num) >= 0.5f) ? Ceiling(num) : Floor(num);
    }

    constexpr float ToDegrees(const float rad)
    {
        return rad * 57.295779513f;
    }

    constexpr float ToRadians(const float deg)
    {
        return deg * 0.0174532925f;
    }
}