//
//  Matrix.cpp
//  X2D_xcode
//
//  Created by roton on 17/1/17.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Matrix.h"

#define MAT33(mat, row, col) mat[(col * 3) + row]
#define MAT44(mat, row, col) mat[(col << 2) + row]

//mat impl
//-----------------------------------------------------------------
Matrix3 Matrix3::operator*(const Matrix3 &rMat3) const
{
    Matrix3 mat3;

    for (int i = 0; i < 3; i++)
    {
        float ai0 = MAT33(m, i, 0), ai1 = MAT33(m, i, 1),  ai2 = MAT33(m, i, 2);
        MAT33(mat3.m, i, 0) = ai0 * MAT33(rMat3.m, 0, 0) + ai1 * MAT33(rMat3.m, 1, 0) + ai2 * MAT33(rMat3.m, 2, 0);
        MAT33(mat3.m, i, 1) = ai0 * MAT33(rMat3.m, 0, 1) + ai1 * MAT33(rMat3.m, 1, 1) + ai2 * MAT33(rMat3.m, 2, 1);
        MAT33(mat3.m, i, 2) = ai0 * MAT33(rMat3.m, 0, 2) + ai1 * MAT33(rMat3.m, 1, 2) + ai2 * MAT33(rMat3.m, 2, 2);
    }

    return mat3;
}

//-----------------------------------------------------------------
Matrix4 Matrix4::operator*(const Matrix4 &rMat4) const
{
    Matrix4 mat4;

    for (int i = 0; i < 4; i++)
    {
        float ai0 = MAT44(m, i, 0), ai1 = MAT44(m, i, 1),  ai2 = MAT44(m, i, 2), ai3 = MAT44(m, i, 3);
        MAT44(mat4.m, i, 0) = ai0 * MAT44(rMat4.m, 0, 0) + ai1 * MAT44(rMat4.m, 1, 0) + ai2 * MAT44(rMat4.m, 2, 0) + ai3 * MAT44(rMat4.m, 3, 0);
        MAT44(mat4.m, i, 1) = ai0 * MAT44(rMat4.m, 0, 1) + ai1 * MAT44(rMat4.m, 1, 1) + ai2 * MAT44(rMat4.m, 2, 1) + ai3 * MAT44(rMat4.m, 3, 1);
        MAT44(mat4.m, i, 2) = ai0 * MAT44(rMat4.m, 0, 2) + ai1 * MAT44(rMat4.m, 1, 2) + ai2 * MAT44(rMat4.m, 2, 2) + ai3 * MAT44(rMat4.m, 3, 2);
        MAT44(mat4.m, i, 3) = ai0 * MAT44(rMat4.m, 0, 3) + ai1 * MAT44(rMat4.m, 1, 3) + ai2 * MAT44(rMat4.m, 2, 3) + ai3 * MAT44(rMat4.m, 3, 3);
    }

    return mat4;
}