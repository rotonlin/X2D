//
//  TextureLoader.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef TextureLoader_h
#define TextureLoader_h

#include "core/Macros.h"
#include "res/ResourceManager.h"

class TextureLoader : public ResourceLoader
{
public:
	TextureLoader();
    ~TextureLoader();

	virtual bool Detect(const std::string& fileName);
	virtual bool Load(const std::string& fileName);
};

#endif /* TextureLoader_h */
