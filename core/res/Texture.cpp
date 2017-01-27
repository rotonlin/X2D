//
//  Texture.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "res/Texture.h"
#include "res/Image.h"

Texture::Texture()
    : _iTexture(0)
    , _eType(NULL_TEX)
{

}

Texture::~Texture()
{
    if (_iTexture)
    {
        glDeleteTextures(1, &_iTexture);
    }
}

void Texture::LoadImage(Image *pImage)
{
    if (_iTexture)
    {
        glDeleteTextures(1, &_iTexture);
    }

    glGenTextures(1, &_iTexture);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, _iTexture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    uint32_t format = GL_RGBA;
    if (pImage->GetFormat() == Image::FORMAT_RGB) format = GL_RGB;
    else if(pImage->GetFormat() == Image::FORMAT_RGBA) format = GL_RGBA;
    else if(pImage->GetFormat() == Image::FORMAT_GRAYSCALE) format = GL_RED;
    else if(pImage->GetFormat() == Image::FORMAT_GRAYSCALE_ALPHA) format = GL_RG;
    else if(pImage->GetFormat() == Image::FORMAT_INDEXED_ALPHA) format = GL_RG;
    else if(pImage->GetFormat() == Image::FORMAT_INDEXED) format = GL_RED;

    glTexImage2D(GL_TEXTURE_2D, 0, format, pImage->Width(), pImage->Height(),
                 0, format, GL_UNSIGNED_BYTE, pImage->Data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    _rect._origin = mathfu::vec2(0, 0);
    _rect._size._width = pImage->Width();
    _rect._size._height = pImage->Height();
    _subRect = _rect;
}

//-----------------------------------
ImageTexture::ImageTexture(Image* pImage)
{
    LoadImage(pImage);
    _eType = IMAGE;
}

//-----------------------------------
AltlasTesture::AltlasTesture(Image* pImage)
{
    LoadImage(pImage);
    _eType = ALTLAS;
}

AltlasTesture::~AltlasTesture()
{

}

void AltlasTesture::AddAltla(const std::string &name, Ref<Altlas> altla)
{
    _altlas[name] = altla;
}

Ref<Texture> AltlasTesture::GetAltla(const std::string &name)
{
    if (_altlas.find(name) != _altlas.end())
    {
        return _altlas[name];
    }
    return nullptr;
}

//-----------------------------------
void Altlas::Init(const Rectf &rRec, const Rectf &rRecSub)
{
    _rect = rRec;
    _subRect = rRecSub;
}

Altlas::Altlas()
{

}

Altlas::~Altlas()
{
    
}





