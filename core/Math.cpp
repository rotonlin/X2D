//
//  Math.cpp
//  X2D_xcode
//
//  Created by roton on 17/1/15.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Math.h"

//vectors impl
void Vector2::Add(const Vector2 &rVec)
{
    x += rVec.x;
    y += rVec.y;
}

void Vector2::Sub(const Vector2 &rVec)
{
    x -= rVec.x;
    y -= rVec.y;
}

float Vector2::Dot(const Vector2 &rVec)
{
    return x * rVec.x + y * rVec.y;
}

float Vector2::Cross(const Vector2 &rVec)
{
    return x * rVec.y - y * rVec.y;
}

void Vector3::Add(const Vector3 &rVec)
{
    x += rVec.x;
    y += rVec.y;
    z += rVec.z;
}

void Vector3::Sub(const Vector3 &rVec)
{
    x -= rVec.x;
    y -= rVec.y;
    z -= rVec.z;
}

float Vector3::Dot(const Vector3 &rVec)
{
    return x * rVec.x + y * rVec.y + z * rVec.z;
}

void Vector3::Cross(const Vector3 &rVec)
{
    float tx = y * rVec.z - z * rVec.y;
    float ty = z * rVec.x - x * rVec.z;
    float tz = x * rVec.y - y * rVec.x;
    x = tx;
    y = ty;
    z = tz;
}

//-----------------------------------------------------------------