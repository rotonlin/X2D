//
//  Texture.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include "core/Macros.h"
#include "res/Resource.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <GL/glew.h>
#endif

class Image;

class Texture : public Resource
{
public:
    Texture(Image* pImage);
    Texture() : _iTexture(0) {}
    ~Texture();

    _FORCE_INLINE_ GLuint TID() const { return _iTexture; }

private:
    GLuint _iTexture;
};

#endif /* Texture_h */
