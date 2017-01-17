//
//  Matrix.h
//  X2D_xcode
//
//  Created by roton on 17/1/17.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Math_Matrix_h
#define Math_Matrix_h

#include "core/math/Vector.h"

//--------------------------------------------------------------------
// Matrix functions
struct Matrix3
{
    float m[9];

    inline Vector3 GetMatrixColumn(int iColumn)
    {
        Vector3 res;
        memcpy(&res, &m[iColumn * 3], sizeof(Vector3));
        return res;
    }

    inline void SetMatrixColumn(const Vector3& rVec, int iColumn)
    {
        memcpy(m + (3 * iColumn), &rVec, sizeof(Vector3));
    }

    // Multiply
    Matrix3 operator * (const Matrix3& rMat3) const;
};

struct Matrix4
{
    float m[16];

    inline Vector4 GetMatrixColumn(int iColumn)
    {
        Vector4 res;
        memcpy(&res, &m[iColumn * 4], sizeof(Vector4));
        return res;
    }

    inline void SetMatrixColumn(const Vector4& rVec, int iColumn)
    {
        memcpy(m + (4 * iColumn), &rVec, sizeof(Vector4));
    }

    // Extract a rotation matrix from a 4x4 matrix
    // Extracts the rotation matrix (3x3) from a 4x4 matrix
    inline Matrix3 ExtractRotationMatrix3()
    {
        Matrix3 mat3;
        memcpy(mat3.m, m, sizeof(Vector3)); // X column
        memcpy(mat3.m + 3, m + 4, sizeof(Vector3)); // Y column
        memcpy(mat3.m + 6, m + 8, sizeof(Vector3)); // Z column
        return mat3;
    }

    // Inject Rotation (3x3) into a full 4x4 matrix
    inline void InjectRotationMatrix4(const Matrix3& src)
    {
        memcpy(m, src.m, sizeof(Vector3));
        memcpy(m + 4, src.m + 3, sizeof(Vector3));
        memcpy(m + 8, src.m + 6, sizeof(Vector3));
    }

    Matrix4 operator * (const Matrix4& rMat4) const;
};

#endif /* Matrix_h */
