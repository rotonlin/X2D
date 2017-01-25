//
//  Application.cpp
//  X2D
//
//  Created by roton on 17/1/25.
//  Copyright © 2017年 roton. All rights reserved.
//
#include "Application.h"

#include <cstdio>

#include "render/Render_GLES.h"
#include "SDL.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run(int argc, char *argv[])
{
	Render_GLES::getSingleton().Init();

	bool bOver = false;
	int frames = 0;

	uint32_t then = SDL_GetTicks();
	while (!bOver)
	{
		++frames;
		uint32_t now = SDL_GetTicks();
		then = now;

		/* Check for events */
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{

		}

		Render_GLES::getSingleton().UpdateScene(1.0f * (now - then) / 1000.0f);

		Render_GLES::getSingleton().BegainDraw();

		Render_GLES::getSingleton().DrawScene();

		Render_GLES::getSingleton().EndDraw();
	}
}