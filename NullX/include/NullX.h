/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#pragma once

#include <math.h>
#include <vector>
#include <intrin.h>

namespace NullX
{
    constexpr float e         = 2.71828182f;
    constexpr float Pi        = 3.14159265f;
    constexpr float TwoPi     = Pi * 2.0f;
    constexpr float HalfPi    = Pi / 2.0f;
    constexpr float ThirdPi   = Pi / 3.0f;
    constexpr float QuarterPi = Pi / 4.0f;

    // Forward Declarations
    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix4;
    class Quaternion;

    /// Contains functionality necessary for performing Vector2 operations
    class __declspec(align(16)) Vector2
    {
    public:
        union
        {
            struct
            {
                /// x coordinate
                float x;
                /// y coordinate
                float y;
            };

            /// Array representing elements of Vector2 -> [0] = x, [1] = y
            float elements[2];

            /// Vector representing elements of Vector2 used for SIMD functions
            __m128 elementsSIMD;
        };

        /// Vector2 representing Up in 2D space (0, 1)
        static Vector2 Up;
        /// Vector2 representing Down in 2D space (0, -1)
        static Vector2 Down;
        /// Vector2 representing Left in 2D space (-1, 0)
        static Vector2 Left;
        /// Vector2 representing Right in 2D space (1, 0)
        static Vector2 Right;

        /// Vector2 Default Constructor. Initializes elements to 0.0f
        Vector2();
        /// Vector2 Constructor.  Sets elements equal to given values
        Vector2(float _x, float _y);
        /// Vector2 Constructor.  Sets elements equal to given __m128
        Vector2(__m128 vec);
        /// Vector2 Constructor.  Sets elements equal to given Vector2
        Vector2(const Vector2& vec);
        /// Vector2 Constructor.  Sets elements equal to given Vector3
        Vector2(const Vector3& vec);
        /// Vector2 Constructor.  Sets elements equal to given Vector4
        Vector2(const Vector4& vec);

        /// Normalizes the Vector2 to unit length
        void Normalize();
        
        /// Calculates the magnitude of the given vector
        /// \return magnitude of vec
        static float   Magnitude(const Vector2& vec);
        
        /// Calculates the squared magnitude of the given vector
        /// \return squared magnitude of vec
        static float   MagnitudeSqr(const Vector2& vec);
        
        /// Calculates the dot product between the given vectors
        /// \return dot product of vec1 & vec2
        static float   Dot(const Vector2& vec1, const Vector2& vec2);

        /// Calculates the angle between the given vectors
        /// \return angle in radians between vec1 & vec2
        static float   Angle(Vector2& vec1, Vector2& vec2);

        /// Calculates the distance between the given vectors
        /// \return distance between vec1 & vec2
        static float   Distance(Vector2& vec1, Vector2& vec2);

        /// Calculates the normalized version of the given vector
        /// \return vec normalized
        static Vector2 Normalized(const Vector2& vec);

        /// Clamps the given vector to a maximum magnitude of mag
        /// \return vec clamped to maximum length of mag
        static Vector2 Clamp(Vector2& vec, const float mag);

        /// Projects vec1 onto vec2
        /// \return projection of vec1 onto vec2
        static Vector2 Projection(Vector2& vec1, Vector2& vec2);

        /// Transforms a Vector2 into a Vector3
        /// \return given Vector2 as Vector3
        static Vector3 ToVector3(const Vector2& vec);

        /// Transforms a Vector2 into a Vector4
        /// \return given Vector2 as Vector4
        static Vector4 ToVector4(const Vector2& vec, const float w);

        /// Compares the elements between two vectors to determine if they are equal
        /// \return true if all elements are equal, false if not
        bool operator    == (const Vector2& vec);
        
        /// Compares the elements between two vectors to determine if they are inequal
        /// \return true if any elements are inequal, false if not
        bool operator    != (const Vector2& vec);

        /// Returns the element at the given index
        /// \return element at index num
        float operator   [] (const int num);

        /// Calculates the addition between this and vec
        Vector2 operator +  (const Vector2& vec);
        /// Calculates the difference between this and vec
        Vector2 operator -  (const Vector2& vec);
        /// Calculates the multiplication of the elements of this and num
        Vector2 operator *  (const float num);
        /// Calculates the division of the elements of this and num
        Vector2 operator /  (const float num);
        /// Calculates the addition between this and vec
        Vector2 operator += (const Vector2& vec);
        /// Calculates the difference between this and vec
        Vector2 operator -= (const Vector2& vec);
        /// Calculates the multiplication of the elements of this and num
        Vector2 operator *= (const float num);
        /// Calculates the division of the elements of this and num
        Vector2 operator /= (const float num);
    };

    /// Contains functionality necessary for performing Vector3 operations
    class __declspec(align(16)) Vector3
    {
    public:
        union
        {
            struct
            {
                /// x coordinate
                float x;
                /// y coordinate
                float y;
                /// z coordinate
                float z;
            };

            /// Array representing elements of Vector3 -> [0] = x, [1] = y, [2] = z
            float elements[3];

            /// Vector representing elements of Vector2 used for SIMD functions
            __m128 elementsSIMD;
        };

        /// Vector3 representing Up in 3D space (0, 1, 0)
        static Vector3 Up;
        /// Vector3 representing Down in 3D space (0, -1, 0)
        static Vector3 Down;
        /// Vector3 representing Left in 3D space (-1, 0, 0)
        static Vector3 Left;
        /// Vector3 representing Right in 3D space (1, 0, 0)
        static Vector3 Right;
        /// Vector3 representing Forward in 3D space (0, 0, 1)
        static Vector3 Forward;
        /// Vector3 representing Backward in 3D space (0, 0, -1)
        static Vector3 Backward;

        /// Vector3 Default Constructor.  Initializes elements to 0.0f
        Vector3();
        /// Vector3 Constructor. Sets elements equal to given values
        Vector3(float _x, float _y, float _z);
        /// Vector3 Constructor.  Sets elements equal to given __m128
        Vector3(__m128 vec);
        /// Vector3 Constructor.  Sets elements equal to given Vector2
        Vector3(const Vector2& vec);
        /// Vector3 Constructor.  Sets elements equal to given Vector3
        Vector3(const Vector3& vec);
        /// Vector3 Constructor.  Sets elements equal to given Vector4
        Vector3(const Vector4& vec);

        /// Normalizes Vector3 to unit length
        void Normalize();

        /// Calculates the magnitude of the given vector
        /// \return magnitude of vec
        static float   Magnitude(const Vector3& vec);

        /// Calculates the squared magnitude of the given vector
        /// \return squared magnitude of vec
        static float   MagnitudeSqr(const Vector3& vec);

        /// Calculates the dot product between the given vectors
        /// \return dot product of vec1 & vec2
        static float   Dot(const Vector3& vec1, const Vector3& vec2);

        /// Calculates the angle between the given vectors
        /// \return angle in radians between vec1 & vec2
        static float   Angle(Vector3& vec1, Vector3& vec2);

        /// Calculates the distance between the given vectors
        /// \return distance between vec1 & vec2
        static float   Distance(Vector3& vec1, Vector3& vec2);

        /// Calculates the normalized version of the given vector
        /// \return vec normalized
        static Vector3 Normalized(const Vector3& vec);

        /// Clamps the given vector to a maximum magnitude of mag
        /// \return vec clamped to maximum length of mag
        static Vector3 Clamp(Vector3& vec, const float mag);

        /// Projects vec1 onto vec2
        /// \return projection of vec1 onto vec2
        static Vector3 Projection(Vector3& vec1, Vector3& vec2);

        /// Calculates the cross product between the given vectors
        /// \return cross product between vec1 & vec2
        static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);

        /// Transforms a Vector3 into a Vector2
        /// \return given Vector3 as Vector2
        static Vector2 ToVector2(const Vector3& vec);

        /// Transforms a Vector3 into a Vector4
        /// \return given Vector3 as Vector4
        static Vector4 ToVector4(const Vector3& vec, const float w);

        /// Compares the elements between two vectors to determine if they are equal
        /// \return true if all elements are equal, false if not
        bool operator    == (const Vector3& vec);

        /// Compares the elements between two vectors to determine if they are inequal
        /// \return true if any elements are inequal, false if not
        bool operator    != (const Vector3& vec);

        /// Returns the element at the given index
        /// \return element at index num
        float operator   [] (const int num);

        /// Calculates the addition between this and vec
        Vector3 operator +  (const Vector3& vec);
        /// Calculates the difference between this and vec
        Vector3 operator -  (const Vector3& vec);
        /// Calculates the multiplication of the elements of this and num
        Vector3 operator *  (const float num);
        /// Calculates the division of the elements of this and num
        Vector3 operator /  (const float num);
        /// Calculates the addition between this and vec
        Vector3 operator += (const Vector3& vec);
        /// Calculates the difference between this and vec
        Vector3 operator -= (const Vector3& vec);
        /// Calculates the multiplication of the elements of this and num
        Vector3 operator *= (const float num);
        /// Calculates the division of the elements of this and num
        Vector3 operator /= (const float num);
    };

    /// Contains functionality necessary for performing Vector4 operations
    class __declspec(align(16)) Vector4
    {
    public:
        union
        {
            struct
            {
                /// x coordinate
                float x;
                /// y coordinate
                float y;
                /// z coordinate
                float z;
                /// w coordinate
                float w;
            };

            /// Array representing elements of Vector4 -> [0] = x, [1] = y, [2] = z, [3] = w
            float elements[4];

            /// Vector representing elements of Vector2 used for SIMD functions
            __m128 elementsSIMD;
        };

        /// Vector4 representing Up in 4D space (0, 1, 0, 0)
        static Vector4 Up;
        /// Vector4 representing Down in 4D space (0, -1, 0, 0)
        static Vector4 Down;
        /// Vector4 representing Left in 4D space (-1, 0, 0, 0)
        static Vector4 Left;
        /// Vector4 representing Right in 4D space (1, 0, 0, 0)
        static Vector4 Right;
        /// Vector4 representing Forward in 4D space (0, 0, 1, 0)
        static Vector4 Forward;
        /// Vector4 representing Backward in 4D space (0, 0, -1, 0)
        static Vector4 Backward;

        /// Vector4 Default Constructor.  Initializes elements to 0.0f
        Vector4();
        /// Vector4 Constructor. Sets elements equal to given values
        Vector4(float _x, float _y, float _z, float _w);
        /// Vector4 Constructor.  Sets elements equal to given __m128 & _w
        Vector4(__m128 vec, const float _w);
        /// Vector4 Constructor.  Sets elements equal to given Vector2
        Vector4(const Vector2& vec, const float _w);
        /// Vector4 Constructor.  Sets elements equal to given Vector3
        Vector4(const Vector3& vec, const float _w);
        /// Vector4 Constructor.  Sets elements equal to given Vector4
        Vector4(const Vector4& vec);

        /// Normalizes Vector4 to unit length
        void Normalize();

        /// Calculates the magnitude of the given vector
        /// \return magnitude of vec
        static float   Magnitude(const Vector4& vec);

        /// Calculates the squared magnitude of the given vector
        /// \return squared magnitude of vec
        static float   MagnitudeSqr(const Vector4& vec);

        /// Calculates the dot product between the given vectors
        /// \return dot product of vec1 & vec2
        static float   Dot(const Vector4& vec1, const Vector4& vec2);

        /// Calculates the angle between the given vectors
        /// \return angle in radians between vec1 & vec2
        static float   Angle(Vector4& vec1, Vector4& vec2);

        /// Calculates the distance between the given vectors
        /// \return distance between vec1 & vec2
        static float   Distance(Vector4& vec1, Vector4& vec2);

        /// Calculates the normalized version of the given vector
        /// \return vec normalized
        static Vector4 Normalized(const Vector4& vec);

        /// Clamps the given vector to a maximum magnitude of mag
        /// \return vec clamped to maximum length of mag
        static Vector4 Clamp(Vector4& vec, const float mag);

        /// Projects vec1 onto vec2
        /// \return projection of vec1 onto vec2
        static Vector4 Projection(Vector4& vec1, Vector4& vec2);

        /// Calculates the cross product between the given vectors
        /// \return cross product between vec1 & vec2
        static Vector4 Cross(const Vector4& vec1, const Vector4& vec2);

        /// Transforms a Vector4 into a Vector2
        /// \return given Vector4 as Vector2
        static Vector2 ToVector2(const Vector4& vec);

        /// Transforms a Vector4 into a Vector3
        /// \return given Vector4 as Vector3
        static Vector3 ToVector3(const Vector4& vec);

        /// Compares the elements between two vectors to determine if they are equal
        /// \return true if all elements are equal, false if not
        bool operator    == (const Vector4& vec);

        /// Compares the elements between two vectors to determine if they are inequal
        /// \return true if any elements are inequal, false if not
        bool operator    != (const Vector4& vec);

        /// Returns the element at the given index
        /// \return element at index num
        float& operator  [] (const int num);

        /// Calculates the addition between this and vec
        Vector4 operator +  (const Vector4& vec);
        /// Calculates the difference between this and vec
        Vector4 operator -  (const Vector4& vec);
        /// Calculates the multiplication of the elements of this and num
        Vector4 operator *  (const float num);
        /// Calculates the division of the elements of this and num
        Vector4 operator /  (const float num);
        /// Calculates the addition between this and vec
        Vector4 operator += (const Vector4& vec);
        /// Calculates the difference between this and vec
        Vector4 operator -= (const Vector4& vec);
        /// Calculates the multiplication of the elements of this and num
        Vector4 operator *= (const float num);
        /// Calculates the division of the elements of this and num
        Vector4 operator /= (const float num);
    };

    /// Contains functionality necessary for performing 4x4 matrix operations
    class __declspec(align(16)) Matrix4
    {
    public:
        union
        {
            /// Elements in row major order
            struct {
                float xx, xy, xz, xw;
                float yx, yy, yz, yw;
                float zx, zy, zz, zw;
                float wx, wy, wz, ww;
            };
            
            /// Array representing rows of matrix -> [0] = row1, [1] = row2, [2] = row3, [3] = row4
            Vector4 rows[4];

            /// 2D Array representing elements of matrix
            float matrix[4][4];

            /// Array representing rows of matrix used for SIMD functions
            __m128 matrixSIMD[4];
        };

        /// Matrix4 representing 4x4 Identity matrix
        static Matrix4 Identity;

        /// Matrix4 Default Constructor
        Matrix4();
        /// Matrix4 Constructor.  Sets elements equal to given values
        Matrix4(float _xx, float _xy, float _xz, float _xw,
                float _yx, float _yy, float _yz, float _yw,
                float _zx, float _zy, float _zz, float _zw,
                float _wx, float _wy, float _wz, float _ww);
        /// Matrix4 Constructor.  Sets elements equal to elements in mat
        Matrix4(const Matrix4& mat);

        /// Calculates the inverse of the given matrix
        /// \return inverse of mat
        static Matrix4 Inverse(Matrix4& mat);

        /// Calculates the the transpose of the given matrix
        /// \return transpose of mat
        static Matrix4 Transpose(const Matrix4& mat);

        /// Calculates the determinant of the given matrix
        /// \return determinant of mat
        static float   Determinant(Matrix4& mat);

        /// Calculates the LU Decomposition of the given Matrix4
        static std::vector<Matrix4> LUDecomposition(Matrix4& mat);

        /// Creates a Translation matrix based off of the given values
        static Matrix4 Translate(const float x, const float y, const float z);
        /// Creates a Translation matrix based off of the given Vector3
        static Matrix4 Translate(const Vector3& vec);
        /// Creates a Rotation matrix based off of the given values
        static Matrix4 Rotate(const float roll, const float pitch, const float yaw);
        /// Creates a Rotation matrix based off of the given Vector3 and angle
        static Matrix4 Rotate(const Vector3& vec, const float angle);
        /// Creates a Rotation matrix based off of the given Quaternion
        static Matrix4 Rotate(const Quaternion& quat);
        /// Creates a Rotation matrix around the x-axis
        static Matrix4 RotateX(const float angle);
        /// Creates a Rotation matrix around the y-axis
        static Matrix4 RotateY(const float angle);
        /// Creates a Rotation matrix around the z-axis
        static Matrix4 RotateZ(const float angle);
        /// Creates a Scale matrix based off of the given value
        static Matrix4 Scale(const float num);
        /// Creates a Scale matrix based off of the given values
        static Matrix4 Scale(const float x, const float y, const float z);
        /// Creates a Scale matrix based off of the given Vector3
        static Matrix4 Scale(const Vector3& vec);
        /// Creates an Inverse Translation matrix based off of the given values
        static Matrix4 InvTranslate(const float x, const float y, const float z);
        /// Creates an Inverse Translation matrix based off of the given Vector3
        static Matrix4 InvTranslate(const Vector3& vec);
        /// Creates an Inverse Translation matrix based off of the given Matrix4
        static Matrix4 InvTranslate(const Matrix4& mat);
        /// Creates an Inverse Rotation matrix based off of the given values
        static Matrix4 InvRotate(const float roll, const float pitch, const float yaw);
        /// Creates an Inverse Rotation matrix based off of the given Vector3
        static Matrix4 InvRotate(const Vector3& vec, const float angle);
        /// Creates an Inverse Rotation matrix based off of the given Matrix4
        static Matrix4 InvRotate(const Matrix4& mat);
        /// Creates an Inverse Scale matrix based off of the given value
        static Matrix4 InvScale(const float num);
        /// Creates an Inverse Scale matrix based off of the given values
        static Matrix4 InvScale(const float x, const float y, const float z);
        /// Creates an Inverse Scale matrix based off of the given Vector3
        static Matrix4 InvScale(const Vector3& vec);
        /// Creates an Inverse Scale matrix based off of the given Matrix4
        static Matrix4 InvScale(const Matrix4& mat);

        /// Compares the elements between two matrices to determine if they are equal
        /// \return true if all elements are equal, false if not
        bool operator    == (Matrix4& mat);

        /// Compares the elements between two matrices to determine if they are inequal
        /// \return true if any elements are inequal, false if not
        bool operator    != (Matrix4& mat);

        /// Returns the element at the given index
        /// \return element at index num
        float* operator  [] (const int num);

        /// Calculates the addition between this and mat
        Matrix4 operator +  (const Matrix4& mat);
        /// Calculates the difference between this and mat
        Matrix4 operator -  (const Matrix4& mat);
        /// Calculates the multiplication of this and vec
        Vector4 operator *  (Vector4& vec);
        /// Calculates the multiplication of this and mat
        Matrix4 operator *  (Matrix4& mat);
        /// Calculates the multiplication of this and num
        Matrix4 operator *  (const float num);
        /// Calculates the division of this and num
        Matrix4 operator /  (const float num);
        /// Calculates the addition between this and mat
        Matrix4 operator += (const Matrix4& mat);
        /// Calculates the difference between this and mat
        Matrix4 operator -= (const Matrix4& mat);
        /// Calculates the multiplication of this and mat
        Matrix4 operator *= (Matrix4& mat);
        /// Calculates the multiplication of this and num
        Matrix4 operator *= (const float num);
        /// Calculates the division of this and mat
        Matrix4 operator /= (const float num);
    };

    /// Contains functionality necessary to perform Quaternion operations
    class __declspec(align(16)) Quaternion
    {
    public:
        union 
        {
            struct
            {
                /// w component
                float w;
                /// x component
                float x;
                /// y component
                float y;
                /// z component
                float z;
            };

            /// Array representing elements of Quaternion -> [0] = w, [1] = x, [2] = y, [3] = z
            float elements[4];
        };

        /// Quaternion Default Constructor
        Quaternion();
        /// Quaternion Constructor.  Sets elements equal to the elements in quat
        Quaternion(const Quaternion& quat);
        /// Quaternion Constructor.  Sets elements equal to the given values
        Quaternion( const float _x, const float _y, const float _z, const float angle);
        /// Quaternion Constructor.  Sets elements equal to elements in Vector3 and angle
        Quaternion( const Vector3& vec, const float angle);
        /// Quaternion Constructor.  Sets elements equal to elements in Vector4 and angle
        Quaternion( const Vector4& vec, const float angle);

        /// Normalizes Quaternion to unit length
        void Normalize();

        /// Calculates the magnitude of the given Quaternion
        /// \return magnitude of quat
        static float Magnitude(const Quaternion& quat);

        /// Calculates the squared magnitude of the given Quaternion
        /// \return squared magnitude of quat
        static float MagnitudeSqr(const Quaternion& quat);

        /// Calculates the dot product between the given Quaternions
        /// \return dot product of quat1 and quat2
        static float Dot(const Quaternion& quat1, const Quaternion& quat2);

        /// Calculates the normalized version of the given Quaternion
        /// \return quat normalized
        static Quaternion Normalized(const Quaternion& quat);

        /// Calculates the conjugate of the given Quaternion
        /// \return conjugate of quat
        static Quaternion Conjugate(const Quaternion& quat);

        /// Calculates the inverse of the given Quaternion
        /// \return inverse of quat
        static Quaternion Inverse(const Quaternion& quat);

        /// Calculates the Euler rotations around each axis
        /// \return Vector3 representing rotations around each axis in radians
        static Vector3 ToEuler(const Quaternion& quat);

        /// Calculates the multiplication of this and quat
        Quaternion operator * (const Quaternion& quat);
        /// Calculates the multiplication of this and num
        Quaternion operator * (const float num);
        /// Calculates the divisionof this and num
        Quaternion operator / (const float num);
        /// Calculates the multiplication of this and quat
        Quaternion operator *= (const Quaternion& quat);
        /// Calculates the multiplication of this and num
        Quaternion operator *= (const float num);
        /// Calculates the divisionof this and num
        Quaternion operator /= (const float num);
    };

    /// Calculates the value of num to the pow power
    /// \return num^pow
    extern constexpr float Pow(const float num, const int pow);

    /// Calculates the value of e to the pow power
    /// \return e^pow
    extern constexpr float Exp(const int pow);

    /// Calculates the absolute value of x
    /// \return |x|
    extern constexpr float Abs(const float x);

    /// Calculates and returns the minimum value between x & y
    /// \return minimum value between x & y
    extern constexpr float Min(const float x, const float y);

    /// Calculates and returns the maximum value between x & y
    /// \return maximum value between x & y
    extern constexpr float Max(const float x, const float y);

    /// Clamps the value of num between min & max
    /// \return num clamped between min & max
    extern constexpr float Clamp(const float num, const float min, const float max);

    /// Truncates num down to the nearest integer
    /// \return num truncated down to nearest integer
    extern constexpr float Floor(const float num);

    /// Truncates num up to nearest integer
    /// \return num truncates up to nearest integer
    extern constexpr float Ceiling(const float num);

    /// Rounds num to nearest integer
    /// \return num rounded to nearest integer
    extern constexpr float Round(const float num);
}
