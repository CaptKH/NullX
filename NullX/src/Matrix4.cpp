/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>
#include <memory>

namespace NullX
{
    Matrix4 Matrix4::Identity = Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4::Matrix4()
    {
        memset(matrix, 0, sizeof(Matrix4));
    }

    Matrix4::Matrix4(float _xx, float _xy, float _xz, float _xw,
                     float _yx, float _yy, float _yz, float _yw,
                     float _zx, float _zy, float _zz, float _zw,
                     float _wx, float _wy, float _wz, float _ww) :
                     xx(_xx), xy(_xy), xz(_xz), xw(_xw),
                     yx(_yx), yy(_yy), yz(_yz), yw(_yw),
                     zx(_zx), zy(_zy), zz(_zz), zw(_zw),
                     wx(_wx), wy(_wy), wz(_wz), ww(_ww)
    {
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
        return RotateX(roll) * RotateY(pitch) * RotateY(yaw);
    }

    Matrix4 Matrix4::Rotate(const Vector3& vec, const float angle)
    {
        return Rotate(vec.x * angle, vec.y * angle, vec.z * angle);
    }

    Matrix4 Matrix4::Rotate(const Quaternion& quat)
    {
        Quaternion qNorm = Quaternion::Normalized(quat);
        float wSqr = qNorm.w * qNorm.w;
        float xSqr = qNorm.x * qNorm.x;
        float ySqr = qNorm.y * qNorm.y;
        float zSqr = qNorm.z * qNorm.z;

        return Matrix4(wSqr + xSqr - ySqr - zSqr, (2 * qNorm.x * qNorm.y) - (2 * qNorm.w * qNorm.z), (2 * qNorm.x * qNorm.z) + (2 * qNorm.w * qNorm.y), 0,
                      (2 * qNorm.x * qNorm.y) + (2 * qNorm.w * qNorm.z), wSqr - xSqr + ySqr - zSqr, (2 * qNorm.y * qNorm.z) - (2 * qNorm.w * qNorm.x), 0,
                      (2 * qNorm.x * qNorm.z) - (2 * qNorm.w * qNorm.y), (2 * qNorm.y * qNorm.z) + (2 * qNorm.w * qNorm.x), wSqr - xSqr - ySqr + zSqr, 0,
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
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (matrix[i][j] != mat[i][j])
                    return false;
            }
        }

        return true;
    }

    bool Matrix4::operator != (Matrix4& mat)
    {
        bool equal = true;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (matrix[i][j] != mat[i][j])
                {
                    equal = false;
                    break;
                }
            }
        }

        return !equal;
    }

    float* Matrix4::operator [] (const int num)
    {
        return matrix[num];
    }

    Matrix4 Matrix4::operator + (const Matrix4& mat)
    {
        return Matrix4(xx + mat.xx, xy + mat.xy, xz + mat.xz, xw + mat.xw,
                       yx + mat.yx, yy + mat.yy, yz + mat.yz, yw + mat.yw,
                       zx + mat.zx, zy + mat.zy, zz + mat.zz, zw + mat.zw,
                       wx + mat.wx, wy + mat.wy, wz + mat.wz, 1.0f);
    }

    Matrix4 Matrix4::operator - (const Matrix4& mat)
    {
        return Matrix4(xx - mat.xx, xy - mat.xy, xz - mat.xz, xw - mat.xw,
                       yx - mat.yx, yy - mat.yy, yz - mat.yz, yw - mat.yw,
                       zx - mat.zx, zy - mat.zy, zz - mat.zz, zw - mat.zw,
                       wx - mat.wx, wy - mat.wy, wz - mat.wz, 1.0f);
    }

    Vector4 Matrix4::operator * (Vector4& vec)
    {
        Vector4 toReturn = Vector4(0.0f, 0.0f, 0.0f, vec.w);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                toReturn[i] += matrix[i][j] * vec[j];
            }
        }

        return toReturn;
    }

    Matrix4 Matrix4::operator * (Matrix4& mat)
    {
        Matrix4 toReturn = Matrix4();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    toReturn[j][i] += matrix[j][k] * mat[k][i];
                }
            }
        }

        return toReturn;
    }

    Matrix4 Matrix4::operator * (const float num)
    {
        return Matrix4(xx * num, xy * num, xz * num, xw * num,
                       yx * num, yy * num, yz * num, yw * num,
                       zx * num, zy * num, zz * num, zw * num,
                       wx * num, wy * num, wz * num, 1.0f);
    }

    Matrix4 Matrix4::operator / (const float num)
    {
        return Matrix4(xx / num, xy / num, xz / num, xw / num,
                       yx / num, yy / num, yz / num, yw / num,
                       zx / num, zy / num, zz / num, zw / num,
                       wx / num, wy / num, wz / num, 1.0f);
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