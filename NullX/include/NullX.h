/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#pragma once

#include <math.h>
#include <vector>

namespace NullX
{
    constexpr float e         = 2.71828182f;
    constexpr float Pi        = 3.14159265f;
    constexpr float HalfPi    = Pi / 2.0f;
    constexpr float ThirdPi   = Pi / 3.0f;
    constexpr float QuarterPi = Pi / 4.0f;

    // Forward Declarations
    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix4;

    class Vector2
    {
    public:
        // Member Variables
        union
        {
            struct
            {
                float x;
                float y;
            };

            float elements[2];
        };

        // Constructors
        Vector2();
        Vector2(float _x, float _y);
        Vector2(const Vector2& vec);

        // Member Functions
        void Normalize();

        // Static Variables
        static Vector2 Up;
        static Vector2 Down;
        static Vector2 Left;
        static Vector2 Right;
                       
        // Static Functions
        static Vector2 Normalized(const Vector2& vec);
        static float Magnitude(const Vector2& vec);
        static float MagnitudeSqr(const Vector2& vec);
        static float Dot(const Vector2& vec1, const Vector2& vec2);
        static float Angle(Vector2& vec1, Vector2& vec2);
        static float Distance(Vector2& vec1, Vector2& vec2);
        static Vector2 Clamp(Vector2& vec, const float mag);
        static Vector2 Projection(Vector2& vec1, Vector2& vec2);
        static Vector3 ToVector3(const Vector2& vec);
        static Vector4 ToVector4(const Vector2& vec, const float w);

        // Operator Overloads
        bool operator == (const Vector2& vec);
        bool operator != (const Vector2& vec);
        float operator [] (const int num);
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
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            };

            float elements[3];
        };

        // Constructors
        Vector3();
        Vector3(float _x, float _y, float _z);
        Vector3(const Vector3& vec);

        // Member Functions
        void Normalize();

        // Static Variables
        static Vector3 Up;
        static Vector3 Down;
        static Vector3 Left;
        static Vector3 Right;
        static Vector3 Forward;
        static Vector3 Backward;

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
        static Vector2 ToVector2(const Vector3& vec);
        static Vector4 ToVector4(const Vector3& vec, const float w);

        // Operator Overloads
        bool operator == (const Vector3& vec);
        bool operator != (const Vector3& vec);
        float operator [] (const int num);
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
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };

            float elements[4];
        };

        // Constructors
        Vector4();
        Vector4(float _x, float _y, float _z, float _w);
        Vector4(const Vector4& vec);

        // Member Functions
        void Normalize();

        // Static Variables
        static Vector4 Up;
        static Vector4 Down;
        static Vector4 Left;
        static Vector4 Right;
        static Vector4 Forward;
        static Vector4 Backward;

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
        static Vector2 ToVector2(const Vector4& vec);
        static Vector3 ToVector3(const Vector4& vec);

        // Operator Overloads
        bool operator == (const Vector4& vec);
        bool operator != (const Vector4& vec);
        float& operator [] (const int num);
        Vector4 operator + (const Vector4& vec);
        Vector4 operator - (const Vector4& vec);
        Vector4 operator * (const float num);
        Vector4 operator / (const float num);
        Vector4 operator += (const Vector4& vec);
        Vector4 operator -= (const Vector4& vec);
        Vector4 operator *= (const float num);
        Vector4 operator /= (const float num);
    };

    class Matrix4
    {
    public:
        // Member Variables
        union
        {
            struct {
                float xx, xy, xz, xw;
                float yx, yy, yz, yw;
                float zx, zy, zz, zw;
                float wx, wy, wz, ww;
            };
            
            struct {
                Vector4 rows[4];
            };

            float matrix[4][4];
        };

        // Constructors
        Matrix4();
        Matrix4(float _xx, float _xy, float _xz, float _xw,
                float _yx, float _yy, float _yz, float _yw,
                float _zx, float _zy, float _zz, float _zw,
                float _wx, float _wy, float _wz, float _ww);
        Matrix4(const Matrix4& mat);

        // Member Functions

        // Static Variables
        static Matrix4 Identity;

        // Static Functions
        static Matrix4 Inverse(Matrix4& mat);
        static Matrix4 Transpose(const Matrix4& mat);
        static float Determinant(Matrix4& mat);

        // Transformations
        static Matrix4 Translate(const float x, const float y, const float z);
        static Matrix4 Translate(const Vector3& vec);
        static Matrix4 Rotate(const float roll, const float pitch, const float yaw);
        static Matrix4 Rotate(const Vector3& vec);
        static Matrix4 RotateX(const float deg);
        static Matrix4 RotateY(const float deg);
        static Matrix4 RotateZ(const float deg);
        static Matrix4 Scale(const float num);
        static Matrix4 Scale(const float x, const float y, const float z);
        static Matrix4 Scale(const Vector3& vec);

        // Decompositions 
        static std::vector<Matrix4> LUDecomposition(Matrix4& mat);

        // Operator Overloads
        bool operator == (Matrix4& mat);
        bool operator != (Matrix4& mat);
        float* operator [] (const int num);
        Vector4 operator * (Vector4& vec);
        Matrix4 operator + (const Matrix4& mat);
        Matrix4 operator - (const Matrix4& mat);
        Matrix4 operator * (Matrix4& mat);
        Matrix4 operator * (const float num);
        Matrix4 operator / (const float num);
        Matrix4 operator += (const Matrix4& mat);
        Matrix4 operator -= (const Matrix4& mat);
        Matrix4 operator *= (const float num);
        Matrix4 operator /= (const float num);
    };
}
