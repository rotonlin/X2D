//
//  ResourceCache.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "ResourceCache.h"

ResourceCache* ResourceCache::_gInstance = memnew(ResourceCache);

ResourceCache::ResourceCache()
{

}

ResourceCache::~ResourceCache()
{

}

ResourceCache& ResourceCache::GetSingleton()
{
	return *_gInstance;
}

