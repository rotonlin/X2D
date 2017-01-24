//
//  Program.h
//  X2D
//
//  Created by roton on 17/1/24.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Program_h
#define Program_h

#include "core/Macros.h"
#include "core/Ref.h"
#include <GL/glew.h>  

class Program : public Reference
{
public:
	Program();
    ~Program();
	void Init(const std::string& vs, const std::string& fs);
	GLint GetUniformLocation(const std::string& uniformName);
	void UseProgram();
private:
	GLuint LoadShader(GLenum type, const char *shaderSrc);
	GLuint LoadProgram(const char *vertShaderSrc, const char *fragShaderSrc);

	std::string _vertexSource;
	std::string _fragmentSource;
	GLuint _programObject;
};

#endif /* Object_h */
