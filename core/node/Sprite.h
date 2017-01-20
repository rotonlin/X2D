//
//  Sprite.h
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Sprite_h
#define Core_Sprite_h

#include "node/Node.h"

//---------------------------------------
class Sprite : public Node
{
public:
	Sprite();
    virtual ~Sprite();

protected:
	virtual void Draw();
};

#endif /* Sprite_h */
