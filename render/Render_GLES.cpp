//
//  Render_GLES.cpp
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Render_GLES.h"
#include "render/MatrixStack.h"

//--------------------------------------------------------------------

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

GLuint esLoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
	{
		return 0;
	}

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char *infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error compiling shader:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;

}

GLuint esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = esLoadShader(GL_VERTEX_SHADER, vertShaderSrc);

	if (vertexShader == 0)
	{
		return 0;
	}

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return 0;
	}

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
	{
		return 0;
	}

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char *infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(programObject);
		return 0;
	}

	// Free up no longer needed shader resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return programObject;
}

void Render_GLES::InitImGUI()
{

}

bool Render_GLES::Init()
{
	// Initialize GLEW to setup the OpenGL Function pointers  
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	_pRootScene = memnew(Scene());
	int cnt = _pRootScene->ReferenceCount();
	{
		Ref<Scene> scene = _pRootScene;
		Ref<Scene> pScene2 = scene;

		pScene2 = nullptr;

		for (int i = 0; i < 3; ++i)
		{
			Ref<Sprite> pSprite(new Sprite());
			_pRootScene->AddChild(pSprite);
		}
	}


	/*const char vShaderStr[] =
		"#version 300 es                            \n"
		"layout(location = 0) in vec4 a_position;   \n"
		"layout(location = 1) in vec4 a_color;      \n"
		"out vec4 v_color;                          \n"
		"void main()                                \n"
		"{                                          \n"
		"    v_color = a_color;                     \n"
		"    gl_Position = a_position;              \n"
		"}";


	const char fShaderStr[] =
		"#version 300 es            \n"
		"precision mediump float;   \n"
		"in vec4 v_color;           \n"
		"out vec4 o_fragColor;      \n"
		"void main()                \n"
		"{                          \n"
		"    o_fragColor = v_color; \n"
		"}";

	_programObject = esLoadProgram(vShaderStr, fShaderStr);
	if (_programObject == 0)
	{
		return false;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	memset(_vbos, 0, sizeof(_vbos));
	_vao = 0;*/

    return true;
}

bool Render_GLES::DeInit()
{
    return true;
}

void Render_GLES::DrawTriangles()
{
	// 3 vertices, with (x,y,z) ,(r, g, b, a) per-vertex
	GLfloat vertices[21] =
	{
		0.0f,  0.5f, 0.0f,        // v0
		1.0f,  0.0f, 0.0f, 1.0f,  // c0
		0.0f, -0.5f, 0.0f,        // v1
		0.0f,  1.0f, 0.0f, 1.0f,  // c1
		0.5f,  0.0f, 0.0f,        // v2
		0.0f,  0.0f, 1.0f, 1.0f,  // c2
	};
	// Index buffer data
	GLushort indices[3] = { 0, 1, 2 };

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(_programObject);

	if (_vbos[VERTEX] == 0 && _vbos[INDICES] == 0)
	{
		glGenBuffers(MAX, _vbos);

		glBindBuffer(GL_ARRAY_BUFFER, _vbos[VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 21,
			nullptr, GL_STATIC_DRAW);
		GLfloat *pVertexMapBuffer;
		pVertexMapBuffer = (GLfloat *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 21,
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		if (pVertexMapBuffer == nullptr)
		{
			return;
		}
		memcpy(pVertexMapBuffer, vertices, sizeof(GLfloat) * 21);
		if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
		{
			return;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[INDICES]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3,
			nullptr, GL_STATIC_DRAW);
		GLushort *pIndicesMapBuffer;
		pIndicesMapBuffer = (GLushort *)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * 3,
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		if (pIndicesMapBuffer == nullptr)
		{
			return;
		}
		memcpy(pIndicesMapBuffer, indices, sizeof(GLushort) * 3);
		if (glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE)
		{
			return;
		}
	}

	if (_vao == 0)
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbos[VERTEX]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[INDICES]);

		glEnableVertexAttribArray(VERTEX);
		glEnableVertexAttribArray(COLOR);

		GLuint   offset = 0;
		glVertexAttribPointer(VERTEX, 3,
			GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7,
			(const void *)offset);

		offset += 3 * sizeof(GLfloat);

		glVertexAttribPointer(COLOR,
			4,
			GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7,
			(const void *)offset);
	}
	else
	{
		glBindVertexArray(_vao);
	}

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
}

void Render_GLES::DrawSquare()
{

}