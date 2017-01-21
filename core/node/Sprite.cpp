//
//  Sprite.cpp
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "node/Sprite.h"
#include "render/Render_GLES.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void Sprite::Draw()
{
	Node::Draw();

	RenderCommond cmd;
	cmd._eType = RenderCommond::TRIANGLES;
	cmd._cmdId = _iZOrder;

	//make vertex
	cmd._vert.reserve(4);

	Vertex vert;
	memset(&vert, 0, sizeof(vert));
	vert.color[3] = 1.0;
	memcpy(&vert.position, &_position, sizeof(_position));
	cmd._vert.push_back(vert);

	vert.color[3] = 1.0;
	mathfu::vec2 pos1(_position.x() + _size._width, _position.y());
	memcpy(&vert.position, &pos1, sizeof(pos1));
	cmd._vert.push_back(vert);

	vert.color[3] = 1.0;
	mathfu::vec2 pos2(_position.x(), _position.y() + _size._height);
	memcpy(&vert.position, &pos2, sizeof(pos2));
	cmd._vert.push_back(vert);

	vert.color[3] = 1.0;
	mathfu::vec2 pos3(_position.x() + _size._width, _position.y() + _size._height);
	memcpy(&vert.position, &pos3, sizeof(pos3));
	cmd._vert.push_back(vert);

	//make indices
	const uint16_t indices[6] = { 0, 1, 2, 2, 1, 3 };
	cmd._indices.reserve(6);
	cmd._indices.assign(indices, indices + 6);
	cmd._iElementCount = 6;

	cmd._clipRec._origin = _position;
	cmd._clipRec._size = _size;

	Render_GLES::getSingleton().AddCommond(cmd);
}