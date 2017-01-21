//
//  Node.cpp
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Node.h"
#include "render/Render_GLES.h"

Node::Node()
	: _iZOrder(0)
	, _iSubZOrder(0)
	, _bSortDirty(false)
	, _fRotation(0.0f)
	, _color(0, 0, 0, 1)
	, _parent(nullptr)
{
	_transform = mathfu::mat4::Identity();
	_transformInv = mathfu::mat4::Identity();
}

Node::~Node()
{
	_parent = nullptr;
}

void Node::Draw()
{
	
}

void Node::Update(float fDelta)
{

}

void Node::AddChild(Ref<Node> node)
{
	node->_iZOrder = _iSubZOrder++;
	node->_parent = this;
	_childs.push_back(node);
	_bSortDirty = true;
}

void Node::RemoveChild(Ref<Node> node)
{
	_childs.remove(node);
}

void Node::RemoveFromParent(Ref<Node> self)
{
	if (_parent)
	{
		_parent->RemoveChild(self);
	}
}

void Node::SortChilds()
{
	if (_bSortDirty)
	{
		_childs.sort([this](const Ref<Node>& a, const Ref<Node>& b)->bool
		{
			return a->_iZOrder < b->_iZOrder;
		});
		_bSortDirty = false;
	}
}

void Node::ConvertToGLSpace(mathfu::vec2& rVec2)
{
	const Sizef& rWinSize = Render_GLES::getSingleton().GetWinSize();
	rVec2.y() = rWinSize._height - rVec2.y() - _size._height;
}

void Node::TransForm(const mathfu::mat4& rTransfrom)
{
	 mathfu::mat4::tr
	_transform *= rTransfrom;
	_transformInv = _transform.Inverse();
}