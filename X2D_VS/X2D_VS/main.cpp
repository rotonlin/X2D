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
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GLContext pContext = SDL_GL_CreateContext(pWindow);

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
		int w, h;
		int display_w, display_h;
		SDL_GetWindowSize(pWindow, &w, &h);
		SDL_GL_GetDrawableSize(pWindow, &display_w, &display_h);
		//io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

		//clear color
		glViewport(0, 0, w, h);
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		Render_GLES::getSingleton().DrawScene();

		SDL_GL_SwapWindow(pWindow);
	}

	SDL_free(pWindow);

    return 0;
}

