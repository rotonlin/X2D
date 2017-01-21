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

	printf("%d\n", node.RefCount());
}