//
//  Render_GLES.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Render_GLES_h
#define Render_GLES_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <GL/glew.h>
#endif

#include <vector>
#include "core/node/Scene.h"
#include "render/RenderCommond.h"

typedef void *SDL_GLContext;
struct SDL_Window;
class Program;

class Render_GLES
{
public:
    static Render_GLES& getSingleton();

    bool Init();
    bool DeInit();

	void BegainDraw();
	void EndDraw();
	void UpdateScene(float fDelta);

	void DrawScene(Ref<Scene> pScene);
	void DrawTriangles();
	void DrawSquare();

	void AddCommond(const RenderCommond& rCommond);
	//void DrawImGUILists(ImDrawData* draw_data);

	_FORCE_INLINE_ const Sizef& GetWinSize() const { return _winSize; }
private:
    Render_GLES();
    ~Render_GLES();

	void InitImGUI();
	void DrawNode(Ref<Node> pNode);
	void Clear();
private:
	enum VertexAttribIndex
	{
		VERTEX,
		COLOR,
		UV,
		INDICES,
		MAX,
	};

	GLuint _vao;
	GLuint _vbos[MAX];
	GLuint _projectionLocation;
	GLuint _modelViewLocation;

	Ref<Program> _program;

	std::vector<RenderCommond> _renderCommonds;

	Sizef _winSize;
	mathfu::vec2 _displayFramebufferScale;

	SDL_Window* pWindow;
	SDL_GLContext pContext;

    static Render_GLES* _sInstance;
};

#endif /* Render_GLES_h */
