//
//  Render_GLES.cpp
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Render_GLES.h"

Render_GLES* Render_GLES::_sInstance = new Render_GLES();

Render_GLES::Render_GLES()
{

}

Render_GLES::~Render_GLES()
{
    
}

Render_GLES& Render_GLES::getSingleton()
{
    return *_sInstance;
}

bool Render_GLES::Init()
{
    return true;
}

bool Render_GLES::DeInit()
{
    return true;
}

