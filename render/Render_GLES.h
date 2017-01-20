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

class Render_GLES
{
public:
    static Render_GLES& getSingleton();

    bool Init();
    bool DeInit();

	void DrawTriangles();
	void DrawSquare();

	//void DrawImGUILists(ImDrawData* draw_data);
private:
    Render_GLES();
    ~Render_GLES();

	void InitImGUI();

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

    static Render_GLES* _sInstance;
};

#endif /* Render_GLES_h */
