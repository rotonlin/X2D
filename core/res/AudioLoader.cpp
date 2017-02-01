//
//  AudioLoader.cpp
//  X2D
//
//  Created by roton on 17/1/31.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "AudioLoader.h"
#include "AudioEngine.h"

bool AudioLoader::Detect(const std::string& fileName)
{
    if (fileName.rfind(".bank") != std::string::npos)
    {
        return true;
    }

    return false;
}


Ref<Resource> AudioLoader::Load(const std::string &fileName)
{
    Ref<Resource> res = memnew(Resource);
    
    AudioEngine::GetSingleton().LoadBank(fileName);

    return res;
}
