//
//  Texture.cpp
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "res/Texture.h"
#include "res/Image.h"

Texture::Texture(Image* pImage)
{
    glGenTextures(1, &_iTexture);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, _iTexture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    uint32_t format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, pImage->Width(), pImage->Height(),
                 0, format, GL_UNSIGNED_BYTE, pImage->Data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_iTexture);
}
