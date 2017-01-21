//
//  Sprite.cpp
//  X2D
//
//  Created by roton on 17/1/20.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "node/Scene.h"
#include "render/Render_GLES.h"

Scene::Scene()
{
	_position.x() = 0;
	_position.y() = 0;
	_size = Render_GLES::getSingleton().GetWinSize();
}

Scene::~Scene()
{

}

void Scene::Update(float fDelta)
{
	_size = Render_GLES::getSingleton().GetWinSize();
}