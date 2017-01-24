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
	, _color(0.0f, 0.0f, 0.0f, 1.0f)
	, _parent(nullptr)
	, _fScale(1.0f)
	, _bVisible(true)
	, _bTransformDirty(true)
	, _bClipByParent(false)
{
	_transform = mathfu::mat3::Identity();
	_localTransform = mathfu::mat3::Identity();
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
	if (node.ptr() == this)
	{
		return;
	}
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

void Node::GetGloblePosition(mathfu::vec2& rVec2)
{
	rVec2 = _position;
	Node* p = _parent;
	while (p != nullptr)
	{
		rVec2 += p->Position();
		p = p->_parent;
	}
	ConvertToGLSpace(rVec2);
}

const mathfu::mat3& Node::TransformLocal()
{
	//should check transform dirty
	//if (_bTransformDirty)
	{
		_localTransform = mathfu::mat3::Identity();

		_localTransform *= mathfu::mat3::FromTranslationVector(_position);

		if (_fRotation != 0.0f)
		{
			_fRotation += 0.05;
			_localTransform *= mathfu::mat3::RotationPoint(_fRotation, Center());
		}

		if (_fScale != 1.0f)
		{
			_localTransform *= mathfu::mat3::FromScaleVector(mathfu::vec2(_fScale));
		}

		_bTransformDirty = false;
	}

	return _localTransform;
}