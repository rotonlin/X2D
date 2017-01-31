//
//  Application.cpp
//  X2D
//
//  Created by roton on 17/1/25.
//  Copyright © 2017年 roton. All rights reserved.
//
#include "Application.h"

#include <cstdio>

#include "res/ResourceManager.h"
#include "res/ImageLoader.h"
#include "render/Render_GLES.h"
#include "Timer.h"
#include "AudioEngine.h"
#include "SDL.h"

Application* Application::_gInstance = memnew(Application);

Application::Application()
{

}

Application::~Application()
{

}

Application& Application::GetSingleton()
{
    return *_gInstance;
}

void Application::RunScene(Ref<Scene> pScene)
{
    if (_pCurScene.ptr())
    {
        _pCurScene->DeInit();
    }
    _pCurScene = pScene;
    _pCurScene->Init();
}

void Application::Init()
{
    //for init
    ResourceManager::GetSingleton().AddLoader(memnew(ImageLoader));
    Render_GLES::getSingleton().Init();
    AudioEngine::GetSingleton().Init();
}

const Sizef& Application::GetWinSize() const
{
    return Render_GLES::getSingleton().GetWinSize();
}

int Application::Run(int argc, char *argv[])
{
	bool bOver = false;
	int frames = 0;

	uint32_t then = SDL_GetTicks();
	while (!bOver)
	{
        /* Check for events */
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            
        }

		++frames;
		uint32_t now = SDL_GetTicks();

        TimerEngine::GetSingleton().Update(now - then);
        AudioEngine::GetSingleton().Update();

        if (_pCurScene.ptr())
        {
            Render_GLES::getSingleton().BegainDraw();
            Render_GLES::getSingleton().DrawScene(_pCurScene);
            Render_GLES::getSingleton().EndDraw();
        }

        then = now;
	}

    //deinit systems
    Render_GLES::getSingleton().DeInit();

    return 0;
}
