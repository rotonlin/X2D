//
//  Math.h
//  X2D_xcode
//
//  Created by roton on 17/1/15.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include <math.h>

namespace Math
{
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

    //--------------------------------------------------------------------
    //base vectors
    struct Vector2
    {
        float x, y;
        Vector2(float _x, float _y)
            : x(_x)
            , y(_y)
        {}
        Vector2(){}

        inline float CrossVector(const Vector2& u, const Vector2& v) const
        {
            return u.x * v.y - u.y * v.x;
        }

        inline float GetVectorLengthSquared() const
        {
            return x * x + y * y;
        }

        inline float GetVectorLength() const
        {
            return sqrtf(GetVectorLengthSquared());
        }

        inline float GetDistanceSquared(const Vector2& rVec) const
        {
            return (x - rVec.x) * (x - rVec.x) + (y - rVec.y) * (y - rVec.y);
        }

        inline float GetDistance(const Vector2& rVec) const
        {
            return sqrtf(GetDistanceSquared(rVec));
        }

        inline void Normalize()
        {
            operator *= (1.0f / GetVectorLength());
        }

        // Angle between vectors, Angle is in radians
        inline float GetAngleBetweenVectors(const Vector2& v)
        {
            float fTemp = operator*(v);
            return float(acos(double(fTemp)));
        }

        inline Vector2 operator + (const Vector2 &rVec) const
        {
            Vector2 vec;
            vec.x = x + rVec.x;
            vec.y = y + rVec.y;
            return vec;
        }

        inline Vector2 operator - (const Vector2 &rVec) const
        {
            Vector2 vec;
            vec.x = x - rVec.x;
            vec.y = y - rVec.y;
            return vec;
        }

        inline void operator *= (float fScale)
        {
            x *= fScale;
            y *= fScale;
        }

        inline Vector2 operator * (float fScale) const
        {
            Vector2 vec;
            vec.x = x * fScale;
            vec.y = y * fScale;
            return vec;
        }

        //dot
        inline float operator * (const Vector2 &rVec) const
        {
            return x * rVec.x + y * rVec.y;
        }
    };

    struct Vector3
    {
        float x, y, z;
        Vector3(float _x, float _y, float _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {}
        Vector3(){}

        inline Vector3 CrossVector(const Vector3& u, const Vector3& v) const
        {
            Vector3 result;
            result.x = u.y * v.z - v.y * u.z;
            result.y = v.x * u.z - u.x * v.z;
            result.z = u.x * v.y - v.x * u.y;
            return result;
        }

        inline float GetVectorLengthSquared() const
        {
            return x * x + y * y + z * z;
        }

        inline float GetVectorLength() const
        {
            return sqrtf(GetVectorLengthSquared());
        }

        inline float GetDistanceSquared(const Vector3& rVec) const
        {
            return (x - rVec.x) * (x - rVec.x) + (y - rVec.y) * (y - rVec.y) + (z - rVec.z) * (z - rVec.z);
        }

        inline float GetDistance(const Vector3& rVec) const
        {
            return sqrtf(GetDistanceSquared(rVec));
        }

        inline void Normalize()
        {
            operator *= (1.0f / GetVectorLength());
        }

        inline float GetAngleBetweenVectors(const Vector3& v)
        {
            float fTemp = operator*(v);
            return float(acos(double(fTemp)));
        }

        inline Vector3 operator + (const Vector3 &rVec) const
        {
            Vector3 vec;
            vec.x = x + rVec.x;
            vec.y = y + rVec.y;
            vec.z = z + rVec.z;
            return vec;
        }

        inline Vector3 operator - (const Vector3 &rVec) const
        {
            Vector3 vec;
            vec.x = x - rVec.x;
            vec.y = y - rVec.y;
            vec.z = z - rVec.z;
            return vec;
        }

        inline void operator *= (float fScale)
        {
            x *= fScale;
            y *= fScale;
            z *= fScale;
        }

        inline Vector3 operator * (float fScale) const
        {
            Vector3 vec;
            vec.x = x * fScale;
            vec.y = y * fScale;
            vec.z = z * fScale;
            return vec;
        }

        //dot
        inline float operator * (const Vector3 &rVec) const
        {
            return x * rVec.x + y * rVec.y + z * rVec.z;
        }
    };

    struct Vector4
    {
        float x, y, z, w;
        Vector4(float _x, float _y, float _z, float _w)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
        {}
        Vector4(){}

        inline Vector4 operator + (const Vector4 &rVec) const
        {
            Vector4 vec;
            vec.x = x + rVec.x;
            vec.y = y + rVec.y;
            vec.z = z + rVec.z;
            vec.w = w + rVec.w;
            return vec;
        }

        inline Vector4 operator - (const Vector4 &rVec) const
        {
            Vector4 vec;
            vec.x = x - rVec.x;
            vec.y = y - rVec.y;
            vec.z = z - rVec.z;
            vec.w = w - rVec.w;
            return vec;
        }

        inline void operator *= (float fScale)
        {
            x *= fScale;
            y *= fScale;
            z *= fScale;
            w += fScale;
        }

        inline Vector4 operator * (float fScale) const
        {
            Vector4 vec;
            vec.x = x * fScale;
            vec.y = y * fScale;
            vec.z = z * fScale;
            vec.w = w * fScale;
            return vec;
        }

        //dot
        inline float operator * (const Vector4 &rVec) const
        {
            return x * rVec.x + y * rVec.y + z * rVec.z + w * rVec.w;
        }
    };

    //--------------------------------------------------------------------
    // Matrix functions
    struct Matrix3
    {
        float m[9];
    };

    struct Matrix4
    {
        float m[16];
    };


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
}

#endif /* Math_h */
