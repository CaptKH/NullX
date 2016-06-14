/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#pragma once

namespace NullX
{
    class Vector2
    {
    public:
        // Member Variables
        float x;
        float y;

        // Constructors
        Vector2();
        Vector2(float _x, float _y);
        Vector2(const Vector2& vec);

        // Member Functions
        void Normalize();

        // Static Variables
        static Vector2 up;
        static Vector2 down;
        static Vector2 left;
        static Vector2 right;

        // Static Functions
        static Vector2 Normalized(const Vector2& vec);
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

    class Vector3
    {
    public:
        // Member Variables
        float x;
        float y;
        float z;

        // Constructors
        Vector3();
        Vector3(float _x, float _y, float _z);
        Vector3(const Vector3& vec);

        // Member Functions
        void Normalize();

        // Static Variables
        static Vector3 up;
        static Vector3 down;
        static Vector3 left;
        static Vector3 right;
        static Vector3 forward;
        static Vector3 backward;

        // Static Functions
        static Vector3 Normalized(const Vector3& vec);
        static float Magnitude(const Vector3& vec);
        static float MagnitudeSqr(const Vector3& vec);
        static float Dot(const Vector3& vec1, const Vector3& vec2);
        static float Angle(Vector3& vec1, Vector3& vec2);
        static float Distance(Vector3& vec1, Vector3& vec2);
        static Vector3 Clamp(Vector3& vec, const float mag);
        static Vector3 Projection(Vector3& vec1, Vector3& vec2);
        static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);

        // Operator Overloads
        bool operator == (const Vector3& vec);
        bool operator != (const Vector3& vec);
        Vector3 operator + (const Vector3& vec);
        Vector3 operator - (const Vector3& vec);
        Vector3 operator * (const float num);
        Vector3 operator / (const float num);
        Vector3 operator += (const Vector3& vec);
        Vector3 operator -= (const Vector3& vec);
        Vector3 operator *= (const float num);
        Vector3 operator /= (const float num);
    };

    class Vector4
    {
    public:
        // Member Variables
        float x;
        float y;
        float z;
        float w;

        // Constructors
        Vector4();
        Vector4(float _x, float _y, float _z, float _w);
        Vector4(const Vector4& vec);

        // Member Functions
        void Normalize();

        // Static Variables
        static Vector4 up;
        static Vector4 down;
        static Vector4 left;
        static Vector4 right;
        static Vector4 forward;
        static Vector4 backward;

        // Static Functions
        static Vector4 Normalized(const Vector4& vec);
        static float Magnitude(const Vector4& vec);
        static float MagnitudeSqr(const Vector4& vec);
        static float Dot(const Vector4& vec1, const Vector4& vec2);
        static float Angle(Vector4& vec1, Vector4& vec2);
        static float Distance(Vector4& vec1, Vector4& vec2);
        static Vector4 Clamp(Vector4& vec, const float mag);
        static Vector4 Projection(Vector4& vec1, Vector4& vec2);
        static Vector4 Cross(const Vector4& vec1, const Vector4& vec2);

        // Operator Overloads
        bool operator == (const Vector4& vec);
        bool operator != (const Vector4& vec);
        Vector4 operator + (const Vector4& vec);
        Vector4 operator - (const Vector4& vec);
        Vector4 operator * (const float num);
        Vector4 operator / (const float num);
        Vector4 operator += (const Vector4& vec);
        Vector4 operator -= (const Vector4& vec);
        Vector4 operator *= (const float num);
        Vector4 operator /= (const float num);
    };
}
