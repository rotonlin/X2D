#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif // _DEBUG
//#include "render/MatrixStack.h"
#include <cstdio>
#include <cstdlib>
#include "render/Render_GLES.h"
#include "core/Object.h"
#include "core/Ref.h"

#include "mathfu/matrix.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main()
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Empty Event Test", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "glfwCreateWindow error\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	
	glfwMakeContextCurrent(window);

	if (!Render_GLES::getSingleton().Init(window))
	{

	}

	// Game loop  
	double time = glfwGetTime();
	bool bOver = false;

	while (!bOver)
	{
		if (glfwWindowShouldClose(window))
		{
			break;
		}

		glfwPollEvents();

		double fTime = glfwGetTime();
		time = fTime;

		// Render 
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(114, 144, 154, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		Render_GLES::getSingleton().DrawTriangles();

		// Swap the screen buffers  
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}