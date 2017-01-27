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
#include "MathUtility.h"

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
    Texture();
    virtual ~Texture();

    enum TexType
    {
        NULL_TEX,
        IMAGE,
        ALTLAS,
    };

    _FORCE_INLINE_ TexType Type() const { return _eType; }
    _FORCE_INLINE_ GLuint TID() const { return _iTexture; }

    void LoadImage(Image* pImage);
    const Rectf& GetRect() const { return _rect; }
    const Rectf& GetSubRect() const { return _subRect; }

    _FORCE_INLINE_ void SetTID(GLuint tex) { _iTexture = tex; }
protected:
    TexType _eType;
    Rectf _rect;
    Rectf _subRect;
private:
    GLuint _iTexture;
};

//image texture
class ImageTexture : public Texture
{
public:
    ImageTexture(Image* pImage);
    ~ImageTexture(){};
};

//Altlas
class Altlas : public Texture
{
public:
    Altlas();
    ~Altlas();

    void Init(const Rectf& rRec, const Rectf& rRecSub);
};

//altlas texture
class AltlasTesture : public Texture
{
public:
    AltlasTesture(Image* pImage);
    ~AltlasTesture();

    void AddAltla(const std::string& name, Ref<Altlas> altla);
    Ref<Texture> GetAltla(const std::string& name);
private:
    std::map<std::string, Ref<Altlas>> _altlas;
};

#endif /* Texture_h */
