//
//  RenderCommond.h
//  X2D
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef RenderCommond_h
#define RenderCommond_h

#include "Macros.h"
#include "Math.h"

struct RenderCommond
{
	enum CommondType
	{
		NULL_TYPE,
		TRIANGLES,
		LINE,
	};

	RenderCommond() : _cmdId(0), _eType(NULL_TYPE)
	{

	}

	~RenderCommond() {}

	int _cmdId;
	CommondType _eType;

	//render datas
	std::vector<Vertex> _vert;
	std::vector<uint16_t> _indices;
	Rectf _clipRec;
	int _iElementCount;
};

#endif /* RenderCommond_h */
