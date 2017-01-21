//
//  Node.h
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Node_h
#define Core_Node_h

#include "Ref.h"
#include "core/Math.h"

//---------------------------------------
class Node : public Reference
{
public:
	Node();
    virtual ~Node();

	void AddChild(Ref<Node> node);

	//setters and getters
	inline void SetZOrder(int iZOrder) { _iZOrder = iZOrder; };
	inline int ZOrder() const { return _iZOrder; }
protected:
	virtual void Draw();
private:
	int _iZOrder;
	int _iSubZOrder;//child added order
	mathfu::vec2 _position;
	Size _size;

	std::vector<Ref<Node>> _childs;
};

#endif /* Node_h */
