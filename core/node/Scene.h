//
//  Scene.h
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Core_Scene_h
#define Core_Scene_h

#include "node/Node.h"

//---------------------------------------
class Scene : public Node
{
public:
	Scene();
    virtual ~Scene();

	virtual void Update(float fDelta);
    virtual void Init();
    virtual void DeInit();
};

#endif /* Scene_h */
