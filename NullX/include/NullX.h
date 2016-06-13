#pragma once

namespace NullX
{
    class Vector2
    {
    public:
        // Member Variables
        float x;
        float y;

        // Static Variables
        static Vector2 up;
        static Vector2 down;
        static Vector2 left;
        static Vector2 right;

        // Constructors
        Vector2();
        Vector2(float _x, float _y);
        Vector2(const Vector2& vec);

        // Member Functions
        void Normalize();

        // Static Functions
        static Vector2 Normalized(Vector2& vec);
        static float Magnitude(const Vector2& vec);
        static float MagnitudeSqr(const Vector2& vec);
        static float Dot(const Vector2& vec1, const Vector2& vec2);
        static float Angle(Vector2& vec1, Vector2& vec2);
        static float Distance(Vector2& vec1, Vector2& vec2);
        static Vector2 Clamp(Vector2& vec, const float mag);
        static Vector2 Projection(Vector2& vec1, Vector2& vec2);

        // Operator Overloads
        bool operator == (const Vector2& vec);
        bool operator != (const Vector2& vec);
        Vector2 operator + (const Vector2& vec);
        Vector2 operator - (const Vector2& vec);
        Vector2 operator * (const float num);
        Vector2 operator / (const float num);
        Vector2 operator += (const Vector2& vec);
        Vector2 operator -= (const Vector2& vec);
        Vector2 operator *= (const float num);
        Vector2 operator /= (const float num);
    };
}
