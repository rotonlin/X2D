//
//  Resource.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Resource.h"
#include "res/ResourceCache.h"

uint64_t Resource::_gResourceId = 0;

Resource::Resource()
{
    _iResId = ++_gResourceId;
}

Resource::~Resource()
{
    //no place to reference the resource, so we remove it from cache
    ResourceCache::GetSingleton().Remove(_path);
}

void Resource::SetPath(const std::string &rPath)
{
    _path = rPath;
    ResourceCache::GetSingleton().Add(rPath, this);
}
