//
//  Shaders.h
//  X2D
//
//  Created by roton on 17/1/27.
//  Copyright © 2017年 roton. All rights reserved.
//

#ifndef Shaders_h
#define Shaders_h

const char vShaderStr[] =
"#version 330                               \n"
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
"#version 330               \n"
"precision mediump float;	\n"
"uniform sampler2D Texture;	\n"
"in vec4 v_color;           \n"
"in vec2 v_uv;				\n"
"out vec4 o_fragColor;      \n"
"void main()                \n"
"{                          \n"
"    o_fragColor = texture(Texture, v_uv) * v_color; \n"
"}";

#endif /* Shaders_h */
