//
//  Math.h
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Math_h
#define Core_Math_h

#include "Macros.h"

struct Vertex
{
	float position[2];
	float color[4];
	float uv[2];
};

struct Sizef
{
	Sizef(){}
	Sizef(float width, float height)
		: _width(width)
		, _height(height)
	{}

	float _width;
	float _height;
};

struct Rectf
{
	Rectf() {}
	Rectf(float x, float y, float width, float height)
		: _origin(x, y)
		, _size(width, height)
	{}
	mathfu::vec2 _origin;
	Sizef _size;
};

#endif /* Math_h */
