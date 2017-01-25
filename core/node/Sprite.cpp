//
//  Sprite.cpp
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "node/Sprite.h"
#include "render/Render_GLES.h"
#include "Math.h"

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

	vert.color = _color;

	//const Sizef& scaleSize = ScaledSize();
	vert.position.x() = 0;
	vert.position.y() = 0;
	cmd._vert.push_back(vert);

	vert.position.x() = _size._width;
	vert.position.y() = 0;
	cmd._vert.push_back(vert);

	vert.position.x() = 0;
	vert.position.y() = _size._height;
	cmd._vert.push_back(vert);

	vert.position.x() = _size._width;
	vert.position.y() = _size._height;
	cmd._vert.push_back(vert);

	//make indices
	const uint16_t indices[6] = { 0, 1, 2, 2, 1, 3 };
	cmd._indices.reserve(6);
	cmd._indices.assign(indices, indices + 6);
	cmd._iElementCount = 6;

	if (_bClipByParent)
	{
		Node* pParent = GetParent();
		if (pParent != nullptr)
		{
			pParent->GetGloblePosition(cmd._clipRec._origin);
			cmd._clipRec._size = pParent->ScaledSize();
		}
	}

	MathUtility::GetMat4(cmd._mv, _transform);

	Render_GLES::getSingleton().AddCommond(cmd);
}
