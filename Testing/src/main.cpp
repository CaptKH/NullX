/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>

using namespace NullX;

int main()
{
    Vector4 v1 = Vector4(1, 1, 1, 1);
    Vector4 v2 = Vector4::Normalized(v1);
    bool f = v1 == v2;

    return 0;
}