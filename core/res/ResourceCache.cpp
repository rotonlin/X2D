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

void ResourceCache::Remove(const std::string &rPath)
{
    if (_cachedResource.find(rPath) != _cachedResource.end())
    {
        _cachedResource.erase(rPath);
    }
}

void ResourceCache::Add(const std::string &rPath, Ref<Resource> pRes)
{
    _cachedResource[rPath] = pRes;
}

Ref<Resource> ResourceCache::GetResource(const std::string& rPath)
{
    if (_cachedResource.find(rPath) != _cachedResource.end())
    {
        return _cachedResource[rPath];
    }
    return nullptr;
}
