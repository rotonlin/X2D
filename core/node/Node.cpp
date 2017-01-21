//
//  Node.cpp
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Node.h"

Node::Node()
	: _iZOrder(0)
	, _iSubZOrder(0)
	, _bSortDirty(false)
{

}

Node::~Node()
{

}

void Node::Draw()
{
	
}

void Node::AddChild(Ref<Node> node)
{
	node->_iZOrder = _iSubZOrder++;
	_childs.push_back(node);
	_bSortDirty = true;
}

void Node::RemoveChild(Ref<Node> node)
{
	_childs.remove(node);
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