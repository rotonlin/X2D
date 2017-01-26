//
//  Image.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Image.h"
#include "res/ResourceCache.h"
#include "res/Texture.h"

Image::Image()
{

}

Image::~Image()
{

}

Ref<Texture> Image::CreateTexture()
{
    std::string texPath = Path() + ".texture";
    Ref<Texture> pTex = ResourceCache::GetSingleton().GetResource(texPath);
    if (!pTex.ptr())
    {
        pTex = memnew(Texture(this));
        pTex->SetPath(texPath);
    }
    return pTex;
}
