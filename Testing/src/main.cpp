/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

using namespace NullX;

int main()
{
    Matrix4 mat = Matrix4::Identity;

    Vector4 vec = Matrix4::Rotate(HalfPi, 0, HalfPi) * Vector4(1.0f, 0.0f, 0.0f, 1.0f);

    Matrix4 mat2 = mat * 5;
    Matrix4 mat3 = mat / 2;

    Matrix4 mat4 = mat2 * mat3;

    mat3 *= 2;

    bool t = mat == mat2;

    return 0;
}