/* ********************************** */
/* NullX Accelerated C++ Math Library */
/* Author: Kirk Hewitt                */
/* Created: 6/12/2016                 */
/* ********************************** */

#include <NullX.h>
#include <math.h>
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

    Matrix4 Matrix4::Inverse(const Matrix4& mat)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Transpose(const Matrix4& mat)
    {
        return Matrix4(mat.xx, mat.yx, mat.zx, mat.wx,
                       mat.xy, mat.yy, mat.zy, mat.wy,
                       mat.xz, mat.yz, mat.zz, mat.wz,
                       mat.xw, mat.yw, mat.zw, mat.ww);
    }

    float Matrix4::Determinant(const Matrix4& mat)
    {
        return 0.0f;
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

    Matrix4 Matrix4::Rotate(const Vector3& vec)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::RotateX(const float deg)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, cosf(deg), -sinf(deg), 0.0f,
                       0.0f, sinf(deg),  cosf(deg), 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotateY(const float deg)
    {
        return Matrix4(cosf(deg), 0.0f,  sinf(deg), 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       -sinf(deg), 0.0f, cosf(deg), 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotateZ(const float deg)
    {
        return Matrix4(cosf(deg), -sinf(deg), 0.0f, 0.0f,
                       sinf(deg),  cosf(deg), 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4* Matrix4::LUDecomposition(const Matrix4& mat)
    {
        return new Matrix4();
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

    Matrix4 Matrix4::operator + (const Matrix4& mat)
    {
        return Matrix4(xx + mat.xx, xy + mat.xy, xz + mat.xz, xw + mat.xw,
                       yx + mat.yx, yy + mat.yy, yz + mat.yz, yw + mat.yw,
                       zx + mat.zx, zy + mat.zy, zz + mat.zz, zw + mat.zw,
                       wx + mat.wx, wy + mat.wy, wz + mat.wz, ww + mat.ww);
    }

    Matrix4 Matrix4::operator - (const Matrix4& mat)
    {
        return Matrix4(xx - mat.xx, xy - mat.xy, xz - mat.xz, xw - mat.xw,
                       yx - mat.yx, yy - mat.yy, yz - mat.yz, yw - mat.yw,
                       zx - mat.zx, zy - mat.zy, zz - mat.zz, zw - mat.zw,
                       wx - mat.wx, wy - mat.wy, wz - mat.wz, ww - mat.ww);
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
                    toReturn[i][j] += matrix[k][j] * mat[i][k];
                }
            }
        }

        toReturn[3][3] = 1.0f;

        return toReturn;
    }

    Matrix4 Matrix4::operator * (const float num)
    {
        return Matrix4(xx * num, xy * num, xz * num, xw * num,
                       yx * num, yy * num, yz * num, yw * num,
                       zx * num, zy * num, zz * num, zw * num,
                       wx * num, wy * num, wz * num, ww * num);
    }

    Matrix4 Matrix4::operator / (const float num)
    {
        return Matrix4(xx / num, xy / num, xz / num, xw / num,
                       yx / num, yy / num, yz / num, yw / num,
                       zx / num, zy / num, zz / num, zw / num,
                       wx / num, wy / num, wz / num, ww / num);
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