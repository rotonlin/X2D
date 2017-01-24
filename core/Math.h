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
	mathfu::vec2 position;
	mathfu::vec4 color;
	mathfu::vec2 uv;
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

namespace math 
{
	_FORCE_INLINE_ void GetMat4(mathfu::mat4& rMat4, const mathfu::mat3& rMat3)
	{
		rMat4[0] = rMat3[0];
		rMat4[1] = rMat3[1];
		rMat4[2] = 0;
		rMat4[3] = rMat3[2];

		rMat4[4] = rMat3[3];
		rMat4[5] = rMat3[4];
		rMat4[6] = 0;
		rMat4[7] = rMat3[5];

		rMat4[8] = 0;
		rMat4[9] = 0;
		rMat4[10] = 1;
		rMat4[11] = 0;

		rMat4[12] = rMat3[6];
		rMat4[13] = rMat3[7];
		rMat4[14] = 0;
		rMat4[15] = rMat3[8];
	}
}

#endif /* Math_h */
