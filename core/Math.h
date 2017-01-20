//
//  Math.h
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Math_h
#define Core_Math_h

#include "mathfu/glsl_mappings.h"

struct Rect
{
	Rect(){}
	Rect(float x, float y, float width, float height)
		: _x(x)
		, _y(y)
		, _width(width)
		, _height(height)
	{}

	float _x;
	float _y;
	float _width;
	float _height;
};

struct Size
{
	Size(){}
	Size(float width, float height)
		: _width(width)
		, _height(height)
	{}

	float _width;
	float _height;
};

#endif /* Math_h */
