//
//  Render_GLES.h
//  X2D_xcode
//
//  Created by roton on 17/1/14.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Render_GLES_h
#define Render_GLES_h

#include <GL/glew.h>  
#include <vector>
#include "core/node/Scene.h"
#include "core/node/Sprite.h"
#include "core/Ref.h"
#include "render/RenderCommond.h"

class Render_GLES
{
public:
    static Render_GLES& getSingleton();

    bool Init();
    bool DeInit();

	void DrawScene();
	void DrawTriangles();
	void DrawSquare();

	void AddCommond(const RenderCommond& rCommond);
	//void DrawImGUILists(ImDrawData* draw_data);
private:
    Render_GLES();
    ~Render_GLES();

	void InitImGUI();
	void DrawNode(Ref<Node> pNode);
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
	GLuint _programObject;
	GLuint _projectionLocation;

	Ref<Scene> _pRootScene;

	std::vector<RenderCommond> _renderCommonds;

    static Render_GLES* _sInstance;
};

#endif /* Render_GLES_h */
