//
//  Math.h
//  X2D_xcode
//
//  Created by roton on 17/1/15.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include "core/Macros.h"

X2D_START

#define VECTOR_METHODS(vector) \
void Add(const vector& rVec);\
void Sub(const vector& rVec);\
float Dot(const vector& rVec);\

//base vectors
struct Vector2
{
    float x, y;
    Vector2(float _x, float _y)
        : x(_x)
        , y(_y)
    {}
    Vector2(){}

    float Cross(const Vector2& rVec);

    VECTOR_METHODS(Vector2)
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

    void Cross(const Vector3& rVec);

    VECTOR_METHODS(Vector3)
};

//mat
struct Matrix3
{
    float m[9];
};

struct Matrix4
{
    float m[16];
};

typedef Vector2 Point2;
typedef Vector3 Point3;

class Math
{
public:

};

X2D_END

#endif /* Math_h */
