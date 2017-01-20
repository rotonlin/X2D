#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif // _DEBUG

#include <cstdio>
#include "render/Render_GLES.h"
#include "SDL.h"

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 0;
	}

	SDL_Window* pWindow = SDL_CreateWindow("test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext pContext = SDL_GL_CreateContext(pWindow);

	Render_GLES::getSingleton().Init();

	bool bOver = false;
	int frames = 0;

	uint32_t then = SDL_GetTicks();
	SDL_Event event;
	while (!bOver) 
	{
		++frames;
		printf("%d\n", frames);

		/* Check for events */
		while (SDL_PollEvent(&event)) 
		{
			
		}
		Render_GLES::getSingleton().DrawTriangles();

		SDL_GL_SwapWindow(pWindow);
	}

	SDL_free(pWindow);

    return 0;
}

