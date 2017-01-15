#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif // _DEBUG

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "render/Render_GLES.h"
#include "core/Object.h"
#include "core/Ref.h"

typedef struct
{
	// Handle to a program object
	GLuint programObject;

	// VertexBufferObject Ids
	GLuint vboIds[2];

	// x-offset uniform location
	GLuint offsetLoc;

} UserData;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(640, 480, "Empty Event Test", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "glfwCreateWindow error\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	
	glfwMakeContextCurrent(window);

	if (!Render_GLES::getSingleton().Init())
	{

	}

	glfwSetKeyCallback(window, key_callback);

	// Game loop  
	double time = glfwGetTime();
	bool bOver = false;

	while (!bOver)
	{
		if (glfwWindowShouldClose(window))
		{
			break;
		}

		double fTime = glfwGetTime();
		printf("%lf\n", fTime - time);
		time = fTime;

		// Render  
		float ratio;
		int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//ratio = width / (float)height;
		//glViewport(0, 0, width, height);

		Render_GLES::getSingleton().DrawTriangles();

		// Swap the screen buffers  
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}