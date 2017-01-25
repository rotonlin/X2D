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

void ResourceManager::Load(const std::string& fileName)
{
	bool bLoadOk = false;

	//ensure cache


	for (int i = 0, l = _loaders.size(); i < l; ++i)
	{
		if (_loaders[i]->Detect(fileName))
		{
			bLoadOk = _loaders[i]->Load(fileName);
			if (bLoadOk)
			{
				break;
			}
		}
	}

	if (!bLoadOk)
	{
		printf("resource %s load faild\n", fileName.c_str());
		assert(0);
	}
}