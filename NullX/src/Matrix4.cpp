/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>
#include <memory>

namespace NullX
{
    Matrix4 Matrix4::Identity = Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 
                                        0.0f, 1.0f, 0.0f, 0.0f, 
                                        0.0f, 0.0f, 1.0f, 0.0f, 
                                        0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4::Matrix4()
    {
        memset(matrix, 0, sizeof(Matrix4));
    }

    Matrix4::Matrix4(float _xx, float _xy, float _xz, float _xw,
                     float _yx, float _yy, float _yz, float _yw,
                     float _zx, float _zy, float _zz, float _zw,
                     float _wx, float _wy, float _wz, float _ww)
    {
        rowsSIMD[0] = _mm_setr_ps(_xx, _xy, _xz, _xw);
        rowsSIMD[1] = _mm_setr_ps(_yx, _yy, _yz, _yw);
        rowsSIMD[2] = _mm_setr_ps(_zx, _zy, _zz, _zw);
        rowsSIMD[3] = _mm_setr_ps(_wx, _wy, _wz, _ww);
    }

    Matrix4::Matrix4(const Matrix4& mat)
    {
        memcpy(matrix, mat.matrix, sizeof(Matrix4));
    }

    Matrix4 Matrix4::Inverse(Matrix4& mat)
    {
        std::vector<Matrix4> decomp = Matrix4::LUDecomposition(mat);
        Matrix4 lower = decomp[0];
        Matrix4 upper = decomp[1];
        Matrix4 toReturn = Matrix4();
        Matrix4 fSub = Matrix4();
        float value = 0.0f;

        // Forward substitution
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                value = Matrix4::Identity[j][i];

                for (int k = 0; k < j; k++)
                {
                    value -= fSub[k][i] * lower[j][k];
                }

                fSub[j][i] = value / lower[j][j];
            }
        }
        
        // Backward substitution
        for (int i = 0; i < 4; i++)
        {
            for (int j = 3; j >= 0; j--)
            {
                value = fSub[j][i];

                for (int k = 3; k > j; k--)
                {
                    value -= toReturn[k][i] * upper[j][k];
                }

                toReturn[j][i] = value / upper[j][j];
            }
        } 

        return toReturn;
    }

    Matrix4 Matrix4::Transpose(const Matrix4& mat)
    {
        return Matrix4(mat.xx, mat.yx, mat.zx, mat.wx,
                       mat.xy, mat.yy, mat.zy, mat.wy,
                       mat.xz, mat.yz, mat.zz, mat.wz,
                       mat.xw, mat.yw, mat.zw, mat.ww);
    }

    float Matrix4::Determinant(Matrix4& mat)
    {
        std::vector<Matrix4> decomp = LUDecomposition(mat);
        return((decomp[0].xx * decomp[0].yy * decomp[0].zz * decomp[0].ww) *
               (decomp[1].xx * decomp[1].yy * decomp[1].zz * decomp[1].ww));
    }

    Matrix4 Matrix4::Perspective(const float fov, const float width, const float height, const float zNear, const float zFar)
    {
        // Credit to HatchitMath for formulas
        // Upon testing non-SIMD version was much faster... I'll come back to this
        float aspect = height / width;
        float depth  = zFar - zNear;
        float xx = 1 / tanf(0.5f * fov);
        float yy = xx * aspect;
        float zz = -(zFar + zNear) / depth;
        float zw = -(2 * zFar * zNear) / depth;

        return Matrix4(xx, 0.0f, 0.0f, 0.0f,
                       0.0f, yy, 0.0f, 0.0f,
                       0.0f, 0.0f, zz, zw,
                       0.0f, 0.0f, -1.0f, 0.0f);
    }

    Matrix4 Matrix4::Orthographic(const float top, const float bottom, const float right, const float left, const float zNear, const float zFar)
    {
        // Credit to HathitMath for formulas
        // Calculate values for diagonal
        __m128 diag1 = _mm_set1_ps(2.0f);
        __m128 diag2 = _mm_setr_ps(right - left, top - bottom, zNear - zFar, 1.0f);
        float* diag3 = _mm_div_ps(diag1, diag2).m128_f32;

        // Calculate values for bottom row
        __m128 bottom1 = _mm_setr_ps(right + left, top + bottom, zFar + zNear, 1.0f);
        __m128 bottom2 = _mm_setr_ps(left - right, bottom - top, zNear - zFar, 1.0f);
        float* bottom3 = _mm_div_ps(bottom1, bottom2).m128_f32;

        return Matrix4(diag3[0], 0.0f, 0.0f, 0.0f,
                       0.0f, diag3[1], 0.0f, 0.0f,
                       0.0f, 0.0f, diag3[2], 0.0f,
                       bottom3[0], bottom3[1], bottom3[2], 1.0f);
    }

    Matrix4 Matrix4::Translate(const float x, const float y, const float z)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, x,
                       0.0f, 1.0f, 0.0f, y,
                       0.0f, 0.0f, 1.0f, z,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::Translate(const Vector3& vec)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, vec.x,
                       0.0f, 1.0f, 0.0f, vec.y,
                       0.0f, 0.0f, 1.0f, vec.z,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::Rotate(const float roll, const float pitch, const float yaw) 
    {
        return RotateX(roll) * RotateY(pitch) * RotateZ(yaw);
    }

    Matrix4 Matrix4::Rotate(const Vector3& vec, const float angle)
    {
        return Rotate(vec.x * angle, vec.y * angle, vec.z * angle);
    }

    Matrix4 Matrix4::Rotate(const Quaternion& quat)
    {
        Quaternion qNorm = Quaternion::Normalized(quat);
        float mag = Quaternion::Magnitude(qNorm);
        float* elementsSqr = _mm_mul_ps(quat.elementsSIMD, quat.elementsSIMD).m128_f32;
        float wSqr = elementsSqr[0];
        float xSqr = elementsSqr[1];
        float ySqr = elementsSqr[2];
        float zSqr = elementsSqr[3];

        return Matrix4(1 - 2 * (ySqr + zSqr), 2 * (qNorm.x * qNorm.y - qNorm.z * qNorm.w), 2 * (qNorm.w * qNorm.y + qNorm.x * qNorm.z), 0,
                       2 * (qNorm.x * qNorm.z + qNorm.w * qNorm.z), 1 - 2 * (xSqr + zSqr), 2 * (qNorm.y * qNorm.z - qNorm.x * qNorm.w), 0,
                       2 * (qNorm.x * qNorm.z - qNorm.y * qNorm.w), 2 * (qNorm.w * qNorm.x + qNorm.y * qNorm.z), 1 - 2 * (xSqr + ySqr), 0,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotateX(const float angle)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, cosf(angle), -sinf(angle), 0.0f,
                       0.0f, sinf(angle),  cosf(angle), 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotateY(const float angle)
    {
        return Matrix4(cosf(angle), 0.0f,  sinf(angle), 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       -sinf(angle), 0.0f, cosf(angle), 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotateZ(const float angle)
    {
        return Matrix4(cosf(angle), -sinf(angle), 0.0f, 0.0f,
                       sinf(angle),  cosf(angle), 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::Scale(const float num)
    {
        return Matrix4(num, 0.0f, 0.0f, 0.0f,
                       0.0f, num, 0.0f, 0.0f,
                       0.0f, 0.0f, num, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::Scale(const float x, const float y, const float z)
    {
        return Matrix4(x, 0.0f, 0.0f, 0.0f,
                       0.0f, y, 0.0f, 0.0f,
                       0.0f, 0.0f, z, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::Scale(const Vector3& vec)
    {
        return Matrix4(vec.x, 0.0f, 0.0f, 0.0f,
                       0.0f, vec.y, 0.0f, 0.0f,
                       0.0f, 0.0f, vec.z, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvTranslate(const float x, const float y, const float z)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, -x,
                       0.0f, 1.0f, 0.0f, -y,
                       0.0f, 0.0f, 1.0f, -z,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvTranslate(const Vector3& vec)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, -vec.x,
                       0.0f, 1.0f, 0.0f, -vec.y,
                       0.0f, 0.0f, 1.0f, -vec.z,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvTranslate(const Matrix4& mat)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, -mat.xw,
                       0.0f, 1.0f, 0.0f, -mat.yw,
                       0.0f, 0.0f, 1.0f, -mat.zw,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvRotate(const float roll, const float pitch, const float yaw)
    {
        return Matrix4::Transpose(Rotate(roll, pitch, yaw));
    }

    Matrix4 Matrix4::InvRotate(const Vector3& vec, const float angle)
    {
        return Matrix4::Transpose(Rotate(vec, angle));
    }
    
    Matrix4 Matrix4::InvRotate(const Matrix4& mat)
    {
        return Matrix4::Transpose(mat);
    }

    Matrix4 Matrix4::InvScale(const float num)
    {
        return Matrix4(1 / num, 0.0f, 0.0f, 0.0f,
                       0.0f, 1 / num, 0.0f, 0.0f,
                       0.0f, 0.0f, 1 / num, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvScale(const float x, const float y, const float z)
    {
        return Matrix4(1 / x, 0.0f, 0.0f, 0.0f,
                       0.0f, 1 / y, 0.0f, 0.0f,
                       0.0f, 0.0f, 1 / z, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvScale(const Vector3& vec)
    {
        return Matrix4(1 / vec.x, 0.0f, 0.0f, 0.0f,
                       0.0f, 1 / vec.y, 0.0f, 0.0f,
                       0.0f, 0.0f, 1 / vec.z, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::InvScale(const Matrix4& mat)
    {
        return Matrix4(1 / mat.xx, 0.0f, 0.0f, 0.0f,
                       0.0f, 1 / mat.yy, 0.0f, 0.0f,
                       0.0f, 0.0f, 1 / mat.zz, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    std::vector<Matrix4> Matrix4::LUDecomposition(Matrix4& mat)
    {
        Matrix4 lower = Matrix4::Identity;
        Matrix4 upper = Matrix4();
        upper.rows[0] = mat.rows[0];
        float value = 0.0f;

        for (int i = 0; i < 3; i++)
        {
            // Lower
            for (int j = i + 1; j < 4; j++)
            {
                value = mat[j][i];
                
                for (int k = 0; k < i; k++)
                {
                    value -= lower[j][k] * upper[k][i];
                }

                lower[j][i] = value / upper[i][i];
            }

            // Upper
            for (int j = 1; j <= i + 1; j++)
            {
                value = mat[j][i + 1];

                for (int k = 0; k < j; k++)
                {
                    value -= lower[j][k] * upper[k][i + 1];
                }

                upper[j][i + 1] = value;
            }
        }

        std::vector<Matrix4> toReturn = std::vector<Matrix4>();
        toReturn.push_back(lower);
        toReturn.push_back(upper);
        return toReturn;
    }

    bool Matrix4::operator == (Matrix4& mat)
    {
        int mask1 = _mm_movemask_ps(_mm_cmpeq_ps(rowsSIMD[0], mat.rowsSIMD[0]));
        int mask2 = _mm_movemask_ps(_mm_cmpeq_ps(rowsSIMD[1], mat.rowsSIMD[1]));
        int mask3 = _mm_movemask_ps(_mm_cmpeq_ps(rowsSIMD[2], mat.rowsSIMD[2]));
        int mask4 = _mm_movemask_ps(_mm_cmpeq_ps(rowsSIMD[3], mat.rowsSIMD[3]));

        return (mask1 == 0xF) ? (mask2 == 0xF) ? (mask3 == 0xF) ? (mask4 == 0xF) ? true : false : false : false : false;
    }

    bool Matrix4::operator != (Matrix4& mat)
    {
        return !(*this == mat);
    }

    float* Matrix4::operator [] (const int num)
    {
        return matrix[num];
    }

    Matrix4 Matrix4::operator + (const Matrix4& mat)
    {
        Matrix4 toReturn = Matrix4(*this);
        toReturn.rowsSIMD[0] = _mm_add_ps(toReturn.rowsSIMD[0], mat.rowsSIMD[0]);
        toReturn.rowsSIMD[1] = _mm_add_ps(toReturn.rowsSIMD[1], mat.rowsSIMD[1]);
        toReturn.rowsSIMD[2] = _mm_add_ps(toReturn.rowsSIMD[2], mat.rowsSIMD[2]);
        toReturn.rowsSIMD[3] = _mm_add_ps(toReturn.rowsSIMD[3], mat.rowsSIMD[3]);

        return toReturn;
    }

    Matrix4 Matrix4::operator - (const Matrix4& mat)
    {
        Matrix4 toReturn = Matrix4(*this);
        toReturn.rowsSIMD[0] = _mm_sub_ps(toReturn.rowsSIMD[0], mat.rowsSIMD[0]);
        toReturn.rowsSIMD[1] = _mm_sub_ps(toReturn.rowsSIMD[1], mat.rowsSIMD[1]);
        toReturn.rowsSIMD[2] = _mm_sub_ps(toReturn.rowsSIMD[2], mat.rowsSIMD[2]);
        toReturn.rowsSIMD[3] = _mm_sub_ps(toReturn.rowsSIMD[3], mat.rowsSIMD[3]);

        return toReturn;
    }

    Vector4 Matrix4::operator * (Vector4& vec)
    {
        return Vector4(_mm_dp_ps(rowsSIMD[0], vec.elementsSIMD, 0xF1).m128_f32[0],
                       _mm_dp_ps(rowsSIMD[1], vec.elementsSIMD, 0xF1).m128_f32[0],
                       _mm_dp_ps(rowsSIMD[2], vec.elementsSIMD, 0xF1).m128_f32[0],
                       _mm_dp_ps(rowsSIMD[3], vec.elementsSIMD, 0xF1).m128_f32[0]);
    }

    Matrix4 Matrix4::operator * (Matrix4& mat)
    {
        Matrix4 toReturn = Matrix4();
        __m128 cols[4] = { _mm_setr_ps(mat.xx, mat.yx, mat.zx, mat.wx),
                           _mm_setr_ps(mat.xy, mat.yy, mat.zy, mat.wy),
                           _mm_setr_ps(mat.xz, mat.yz, mat.zz, mat.wz),
                           _mm_setr_ps(mat.xw, mat.yw, mat.zw, mat.ww) };

        for (int i = 0; i < 4; i++)
        {
            toReturn.rowsSIMD[i] = _mm_setr_ps(_mm_dp_ps(rowsSIMD[i], cols[0], 0xF1).m128_f32[0],
                                   _mm_dp_ps(rowsSIMD[i], cols[1], 0xF1).m128_f32[0],
                                   _mm_dp_ps(rowsSIMD[i], cols[2], 0xF1).m128_f32[0],
                                   _mm_dp_ps(rowsSIMD[i], cols[3], 0xF1).m128_f32[0]);
        }

        toReturn[3][3] = 1.0f;

        return toReturn;
    }

    Matrix4 Matrix4::operator * (const float num)
    {
        Matrix4 toReturn = Matrix4(*this);
        __m128 mult = _mm_set1_ps(num);

        toReturn.rowsSIMD[0] = _mm_mul_ps(toReturn.rowsSIMD[0], mult);
        toReturn.rowsSIMD[1] = _mm_mul_ps(toReturn.rowsSIMD[1], mult);
        toReturn.rowsSIMD[2] = _mm_mul_ps(toReturn.rowsSIMD[2], mult);
        toReturn.rowsSIMD[3] = _mm_mul_ps(toReturn.rowsSIMD[3], mult);

        return toReturn;
    }

    Matrix4 Matrix4::operator / (const float num)
    {
        Matrix4 toReturn = Matrix4(*this);
        __m128 div = _mm_set1_ps(num);

        toReturn.rowsSIMD[0] = _mm_div_ps(toReturn.rowsSIMD[0], div);
        toReturn.rowsSIMD[1] = _mm_div_ps(toReturn.rowsSIMD[1], div);
        toReturn.rowsSIMD[2] = _mm_div_ps(toReturn.rowsSIMD[2], div);
        toReturn.rowsSIMD[3] = _mm_div_ps(toReturn.rowsSIMD[3], div);

        return toReturn;
    }

    Matrix4 Matrix4::operator += (const Matrix4& mat)
    {
        *this = *this + mat;
        return *this;
    }

    Matrix4 Matrix4::operator -= (const Matrix4& mat)
    {
        *this = *this - mat;
        return *this;
    }

    Matrix4 Matrix4::operator *= (Matrix4& mat)
    {
        *this = *this * mat;
        return *this;
    }

    Matrix4 Matrix4::operator *= (const float num)
    {
        *this = *this * num;
        return *this;
    }

    Matrix4 Matrix4::operator /= (const float num)
    {
        *this = *this / num;
        return *this;
    }
}