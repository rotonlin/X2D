//
//  AudioLoader.h
//  X2D
//
//  Created by roton on 17/1/31.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef AudioLoader_h
#define AudioLoader_h

#include "core/Macros.h"
#include "res/ResourceManager.h"
#include "res/Resource.h"

class AudioLoader : public ResourceLoader
{
public:
    AudioLoader(){};
    ~AudioLoader(){};

    virtual bool Detect(const std::string& fileName);
    virtual Ref<Resource> Load(const std::string& fileName);
};

#endif /* AudioLoader_h */
