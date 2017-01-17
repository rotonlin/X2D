//
//  Math.h
//  X2D_xcode
//
//  Created by roton on 17/1/15.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include "core/math/Vector.h"
#include "core/math/Matrix.h"

//--------------------------------------------------------------------
//constants
#define PI (3.14159265358979323846)
#define M_2PI (2.0 * PI)
#define M_PI_DIV_180 (0.017453292519943296)
#define M_180_DIV_PI (57.2957795130823229)

//e.g. DegToRad(90.0)
#define DegToRad(x)	((x)*M_PI_DIV_180)
#define RadToDeg(x)	((x)*M_180_DIV_PI)

// Hour angles
#define HrToDeg(x)	((x) * (1.0 / 15.0))
#define HrToRad(x)	DegToRad(HrToDeg(x))

#define DegToHr(x)	((x) * 15.0))
#define RadToHr(x)	DegToHr(RadToDeg(x))

namespace Math
{

    // Returns the same number if it is a power of
    // two. Returns a larger integer if it is not a
    // power of two. The larger integer is the next
    // highest power of two.
    // NearestPow2<unsigned int>(x)...
    template<typename T>
    inline T NearestPow2(T iValue)
    {
        T nPow2 = 1;

        while(iValue > nPow2)
        {
            nPow2 = (nPow2 << 1);
        }

        return nPow2;
    }

    // LoadIdentity
    inline void LoadIdentity3(Matrix3& m)
    {
        static Matrix3 identity =
        {
            1.0f, 0.0f, 0.0f ,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        memcpy(&m, &identity, sizeof(Matrix3));
    }

    inline void LoadIdentity4(Matrix4& m)
    {
        static Matrix4 identity =
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        memcpy(&m, &identity, sizeof(Matrix4));
    }

    inline void Transform(Vector4& rVec, const Matrix4& rMat)
    {
        rVec.x = rMat.m[0] * rVec.x + rMat.m[4] * rVec.y + rMat.m[8] *  rVec.z + rMat.m[12] * rVec.w;
        rVec.y = rMat.m[1] * rVec.x + rMat.m[5] * rVec.y + rMat.m[9] *  rVec.z + rMat.m[13] * rVec.w;
        rVec.z = rMat.m[2] * rVec.x + rMat.m[6] * rVec.y + rMat.m[10] * rVec.z + rMat.m[14] * rVec.w;
        rVec.w = rMat.m[2] * rVec.x + rMat.m[6] * rVec.y + rMat.m[10] * rVec.z + rMat.m[14] * rVec.w;
    }

    inline void Transform(Vector3& rVec, const Matrix4& rMat)
    {
         rVec.x = rMat.m[0] * rVec.x + rMat.m[4] * rVec.y + rMat.m[8] *  rVec.z + rMat.m[12];
         rVec.y = rMat.m[1] * rVec.x + rMat.m[5] * rVec.y + rMat.m[9] *  rVec.z + rMat.m[13];
         rVec.z = rMat.m[2] * rVec.x + rMat.m[6] * rVec.y + rMat.m[10] * rVec.z + rMat.m[14];
    }

    inline void Transform(Vector2& rVec, const Matrix3& rMat)
    {
        rVec.x = rMat.m[0] * rVec.x + rMat.m[3] * rVec.y + rMat.m[6];
        rVec.y = rMat.m[1] * rVec.x + rMat.m[4] * rVec.y + rMat.m[7];
    }

    inline void Rotate(Vector2& rVec, const Matrix3& rMat)
    {
        rVec.x = rMat.m[0] * rVec.x + rMat.m[3] * rVec.y;
        rVec.y = rMat.m[1] * rVec.x + rMat.m[4] * rVec.y;
    }

    inline void Rotate(Vector3& rVec, const Matrix3& rMat)
    {
        rVec.x = rMat.m[0] * rVec.x + rMat.m[3] * rVec.y + rMat.m[6] * rVec.z;
        rVec.y = rMat.m[1] * rVec.x + rMat.m[4] * rVec.y + rMat.m[7] * rVec.z;
        rVec.z = rMat.m[2] * rVec.x + rMat.m[5] * rVec.y + rMat.m[8] * rVec.z;
    }
}

#endif /* Math_h */
