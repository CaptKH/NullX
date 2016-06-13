#include <NullX.h>

using namespace NullX;

int main()
{
    Vector2 v1 = Vector2::right;
    Vector2 v2 = Vector2::left;

    float angle = Vector2::Distance(v1, v2);
    return 0;
}