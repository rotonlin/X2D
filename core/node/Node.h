//
//  Node.h
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Node_h
#define Core_Node_h

#include "Object.h"
#include "core/Math.h"

//---------------------------------------
class Node : public Object
{
public:
	Node();
    virtual ~Node();
protected:
	virtual void Draw();
private:
	int _iZOrder;
	int _iSubZOrder;//child added order
	mathfu::vec2 _position;
	Size _size;
};

#endif /* Node_h */
