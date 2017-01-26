//
//  RenderCommond.h
//  X2D
//
//  Created by roton on 17/1/21.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef RenderCommond_h
#define RenderCommond_h

#include "Macros.h"
#include "Math.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <GL/glew.h>
#endif

struct RenderCommond
{
	enum CommondType
	{
		NULL_TYPE,
		TRIANGLES,
		LINE,
	};

	RenderCommond() : _cmdId(0), _eType(NULL_TYPE), _texId(0)
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

	//transform
	mathfu::mat4 _mv;

    //tex
    GLuint _texId;
};

#endif /* RenderCommond_h */
