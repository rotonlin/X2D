//
//  Object.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include "core/Macros.h"

class Object
{
public:
    Object();
    virtual ~Object();

	template<class T>
	T *cast_to() 
	{
		if (!this)
		{
			return nullptr;
		}

		return static_cast<T*>(this);
	}
};

#endif /* Object_h */
