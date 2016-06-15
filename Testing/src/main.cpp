/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

using namespace NullX;

int main()
{
    Matrix4 mat = Matrix4(1, 4, 2, 3,
        4, 2, 1, 0,
        0, 6, 7, 1,
        2, 2, 1, 4);

    float det = Matrix4::Determinant(mat);

    return 0;
}