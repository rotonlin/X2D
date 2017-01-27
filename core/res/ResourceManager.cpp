//
//  ResourceManager.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "ResourceManager.h"
#include "ResourceCache.h"

ResourceManager* ResourceManager::_gInstance = memnew(ResourceManager);

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager& ResourceManager::GetSingleton()
{
	return *_gInstance;
}

void ResourceManager::AddLoader(Ref<ResourceLoader> pLoader)
{
	_loaders.push_back(pLoader);
}

Ref<Resource> ResourceManager::Load(const std::string& fileName)
{
	//ensure cache
    Ref<Resource> res = ResourceCache::GetSingleton().GetResource(fileName);
    if (res.ptr())
    {
        return res;
    }


	for (size_t i = 0, l = _loaders.size(); i < l; ++i)
	{
		if (_loaders[i]->Detect(fileName))
		{
			res = _loaders[i]->Load(fileName);
			if (res.ptr())
			{
                return res;
			}
		}
	}


    printf("resource %s load faild\n", fileName.c_str());
    //assert(0);

    return nullptr;
}
