#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif // _DEBUG

#include <cstdio>
#include "render/Render_GLES.h"
#include "SDL.h"

int main(int argc, char *argv[])
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

    return 0;
}

