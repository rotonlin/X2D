//
//  ResourceCache.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef ResourceCache_h
#define ResourceCache_h

#include "core/Macros.h"
#include "core/Ref.h"
#include "res/Resource.h"

class ResourceCache
{
public:
	static ResourceCache& GetSingleton();

private:
	ResourceCache();
	~ResourceCache();

	std::vector<Ref<Resource>> _cachedResource;

	static ResourceCache* _gInstance;
};

#endif /* ResourceCache_h */
