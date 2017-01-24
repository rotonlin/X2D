//
//  Render_GLES.cpp
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#include "Render_GLES.h"
#include "SDL.h"
#include "render/MatrixStack.h"
#include "render/Program.h"

//--------------------------------------------------------------------
static MatrixStack<mathfu::mat3, mathfu::vec2> gMatrixStack;

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

void Render_GLES::InitImGUI()
{

}

bool Render_GLES::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 0;
	}

	pWindow = SDL_CreateWindow("test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	pContext = SDL_GL_CreateContext(pWindow);

	// Initialize GLEW to setup the OpenGL Function pointers  
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	const char vShaderStr[] =
		"#version 300 es                            \n"
		"precision mediump float;					\n"
		"layout(location = 0) in vec2 a_position;   \n"
		"layout(location = 1) in vec4 a_color;      \n"
		"layout(location = 2) in vec2 uv;			\n"
		"uniform mat4 perspective;					\n"
		"uniform mat4 modelview;					\n"
		"out vec4 v_color;                          \n"
		"out vec2 v_uv;								\n"
		"void main()                                \n"
		"{                                          \n"
		"    v_color = a_color;                     \n"
		"    v_uv = uv;										\n"
		"    gl_Position = perspective * modelview * vec4(a_position, 0, 1);	\n"
		"}";


	const char fShaderStr[] =
		"#version 300 es            \n"
		"precision mediump float;	\n"
		"uniform sampler2D Texture;	\n"
		"in vec4 v_color;           \n"
		"in vec4 v_uv;				\n"
		"out vec4 o_fragColor;      \n"
		"void main()                \n"
		"{                          \n"
		"    o_fragColor = v_color; \n"
		"}";

	_program = memnew(Program);
	_program->Init(vShaderStr, fShaderStr);

	_projectionLocation = _program->GetUniformLocation("perspective");
	_modelViewLocation = _program->GetUniformLocation("modelview");

	glGenBuffers(1, &_vbos[VERTEX]);
	glGenBuffers(1, &_vbos[INDICES]);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbos[VERTEX]);

	glEnableVertexAttribArray(VERTEX);
	glEnableVertexAttribArray(COLOR);
	glEnableVertexAttribArray(UV);

	//pointer data offsets
	glVertexAttribPointer(VERTEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(UV, 2, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	//texture creation

	// Restore modified GL state
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_renderCommonds.reserve(200);

    return true;
}

bool Render_GLES::DeInit()
{
	SDL_free(pContext);
	SDL_free(pWindow);

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
	_program->UseProgram();

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

void Render_GLES::Clear()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Render_GLES::DrawScene()
{
	int fb_width = (int)(_winSize._width * _displayFramebufferScale.x());
	int fb_height = (int)(_winSize._height * _displayFramebufferScale.y());
	if (fb_width == 0 || fb_height == 0)
	{
		return;
	}

	//generate commond
	_renderCommonds.clear();

	gMatrixStack.PushMatrix();
	DrawNode(_pRootScene);
	gMatrixStack.PopMatrix();

	Clear();
	glViewport(0, 0, fb_width, fb_height);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	//scissor test
	//glEnable(GL_SCISSOR_TEST);
	//active texture
	//glActiveTexture(GL_TEXTURE0);

	_program->UseProgram();

	glBindVertexArray(_vao);

	//render scene
	for (int i = 0, n = _renderCommonds.size(); i < n; ++i)
	{
		const RenderCommond& commond = _renderCommonds[i];

		//set uniforms 
		mathfu::mat4 OrthoMat = mathfu::mat4::Ortho(0, fb_width, fb_height, 0, -1, 1);
		glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, (const GLfloat*)&OrthoMat);
		glUniformMatrix4fv(_modelViewLocation, 1, GL_FALSE, (const GLfloat*)&commond._mv);


		glBindBuffer(GL_ARRAY_BUFFER, _vbos[VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, commond._vert.size() * sizeof(Vertex), &commond._vert[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[INDICES]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, commond._indices.size() * sizeof(uint16_t), &commond._indices[0], GL_DYNAMIC_DRAW);

		//glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
		glScissor(
			commond._clipRec._origin.x(), 
			commond._clipRec._origin.y(),
			commond._clipRec._size._width,
			commond._clipRec._size._height);

		glDrawElements(GL_TRIANGLES, commond._iElementCount, GL_UNSIGNED_SHORT, 0);
	}

	//clean
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDisable(GL_SCISSOR_TEST);
	glDisable(GL_BLEND);
	glBindVertexArray(0);
}

void Render_GLES::DrawNode(Ref<Node> pNode)
{
	gMatrixStack.MultMatrix(pNode->TransformLocal());
	pNode->SetTransform(gMatrixStack.GetMatrix());

	pNode->Draw();

	for (std::list<Ref<Node>>::iterator iter = pNode->_childs.begin(); iter != pNode->_childs.end(); ++iter)
	{
		if (!((*iter)->Visible()))
		{
			continue;
		}

		//not in view


		//only sort when a new child add to the node , make zorder effect
		pNode->SortChilds();
		gMatrixStack.PushMatrix();
		DrawNode(*iter);
		gMatrixStack.PopMatrix();
	}
}

void Render_GLES::AddCommond(const RenderCommond& rCommond)
{
	_renderCommonds.push_back(rCommond);
}

void Render_GLES::BegainDraw()
{
	int w, h;
	int display_w, display_h;
	SDL_GetWindowSize(pWindow, &w, &h);
	SDL_GL_GetDrawableSize(pWindow, &display_w, &display_h);
	_winSize._width = w;
	_winSize._height = h;
	_displayFramebufferScale = mathfu::vec2(_winSize._width > 0 ? ((float)display_w / w) : 0,
		h > 0 ? ((float)display_h / h) : 0);

	if (_pRootScene == nullptr)
	{
		_pRootScene = memnew(Scene);
		_pRootScene->SetSize(_winSize);
		_pRootScene->SetPosition(mathfu::vec2(0, 0));
		{
			Ref<Sprite> pSprite = memnew(Sprite);
			pSprite->SetPosition(mathfu::vec2(250, 150));
			pSprite->SetSize(Sizef(300.0f, 300.0f));
			pSprite->SetColor(mathfu::vec4(0.5, 0.5, 0.2, 1));
			pSprite->SetRotation(M_PI / 4);
			_pRootScene->AddChild(pSprite);

			Ref<Sprite> pSprite1 = memnew(Sprite);
			pSprite1->SetPosition(pSprite->Center());
			pSprite1->SetSize(Sizef(100.0f, 100.0f));
			pSprite1->SetColor(mathfu::vec4(0.7, 0.3, 0.2, 1));
			pSprite1->SetRotation(-M_PI / 4);
			pSprite1->SetScale(1.2);
			pSprite->AddChild(pSprite1);

			Ref<Sprite> pSprite2 = memnew(Sprite);
			pSprite2->SetPosition(pSprite1->Center());
			pSprite2->SetSize(Sizef(50.0f, 50.0f));
			pSprite2->SetColor(mathfu::vec4(0.2, 0.3, 0.2, 1));
			pSprite2->SetRotation(M_PI / 4);
			//pSprite2->Hide();
			pSprite1->AddChild(pSprite2);

		}

	}
}

void Render_GLES::EndDraw()
{
	SDL_GL_SwapWindow(pWindow);
}

void Render_GLES::UpdateScene(float fDelta)
{
	if (_pRootScene != nullptr)
	{
		_pRootScene->Update(fDelta);
	}
}