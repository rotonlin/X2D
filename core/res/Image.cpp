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
    Ref<ImageTexture> pTex = memnew(ImageTexture(this));

    return pTex;
}

Ref<Texture> Image::CreateAltlaTexture()
{
    Ref<AltlasTesture> pTex = memnew(AltlasTesture(this));

    return pTex;
}
