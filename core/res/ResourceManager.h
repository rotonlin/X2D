//
//  Program.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include "core/Macros.h"
#include "res/Resource.h"

class ResourceLoader : public Reference
{
public:
	virtual bool Detect(const std::string& fileName) = 0;//file path
	virtual Ref<Resource> Load(const std::string& fileName) = 0;
};

class ResourceManager
{
public:
	static ResourceManager& GetSingleton();

    Ref<Resource> Load(const std::string& fileName);
    void AddLoader(Ref<ResourceLoader> pLoader);
private:
	ResourceManager();
	~ResourceManager();

	std::vector<Ref<ResourceLoader>> _loaders;

	static ResourceManager* _gInstance;
};

#endif /* ResourceManager_h */
