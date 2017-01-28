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
#include "render/Shaders.h"

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
		1136,
		640,
		SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	pContext = SDL_GL_CreateContext(pWindow);


    int w, h;
    int display_w, display_h;
    SDL_GetWindowSize(pWindow, &w, &h);
    SDL_GL_GetDrawableSize(pWindow, &display_w, &display_h);
    _winSize._width = w;
    _winSize._height = h;
    _displayFramebufferScale = mathfu::vec2(_winSize._width > 0 ? ((float)display_w / w) : 0,
                                            h > 0 ? ((float)display_h / h) : 0);

#ifdef _WIN32
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return false;
    }
#endif

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
	glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

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

}

void Render_GLES::DrawSquare()
{

}

void Render_GLES::Clear()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Render_GLES::DrawScene(Ref<Scene> pScene)
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
	DrawNode(pScene);
	gMatrixStack.PopMatrix();

    //begin draw
	Clear();
	glViewport(0, 0, fb_width, fb_height);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	//scissor test
	//glEnable(GL_SCISSOR_TEST);

	_program->UseProgram();

	glBindVertexArray(_vao);

	//render scene
	for (size_t i = 0, n = _renderCommonds.size(); i < n; ++i)
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

		if(commond._texId)
            glBindTexture(GL_TEXTURE_2D, commond._texId);

		//glScissor(
		//	commond._clipRec._origin.x(),
		//	commond._clipRec._origin.y(),
		//	commond._clipRec._size._width,
		//	commond._clipRec._size._height);

		glDrawElements(GL_TRIANGLES, commond._iElementCount, GL_UNSIGNED_SHORT, 0);

        if(commond._texId)
            glBindTexture(GL_TEXTURE_2D, 0);
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

}

void Render_GLES::EndDraw()
{
	SDL_GL_SwapWindow(pWindow);
}

