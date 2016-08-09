/****************************************************************************
**
** ShaderData.h
**
** Copyright (C) May 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//---------------------------------------------------------------------------
#ifndef ShaderDataH
#define ShaderDataH
//---------------------------------------------------------------------------
static const char *g_Vert_ShaderData =
"varying vec3 l;\r\n"
"varying vec3 n;\r\n"
"uniform int drawMode;\r\n"
"void main(void)\r\n"
"{\r\n"
"	if (drawMode > 5)\r\n"
"	{\r\n"
"		l = normalize(vec3(gl_LightSource[0].position));\r\n"
"		n = normalize(gl_NormalMatrix * gl_Normal);\r\n"
"	}\r\n"
"	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\r\n"
"	gl_TexCoord[0] = gl_MultiTexCoord0;\r\n"
"	gl_FrontColor = gl_Color;\r\n"
"}";
//---------------------------------------------------------------------------
static const char *g_Frag_DeathShaderData =
"uniform sampler2D usedTexture;\r\n"
"void main(void)\r\n"
"{\r\n"
"	vec4 textureColor = texture2D(usedTexture, gl_TexCoord[0].xy);\r\n"
"	float red = textureColor.r * 0.85;\r\n"
"	if (red == 0.0)\r\n"
"		red = textureColor.g * 0.85;\r\n"
"	gl_FragColor = vec4(red, red, red, textureColor.a) * gl_Color;\r\n"
"}";
//---------------------------------------------------------------------------
static const char *g_Frag_LightShaderData =
"uniform sampler2D usedTexture;\r\n"
"uniform int drawMode;\r\n"
"uniform float colors[96];\r\n"
"void main(void)\r\n"
"{\r\n"
"	vec4 textureColor = texture2D(usedTexture, gl_TexCoord[0].xy);\r\n"
"	if (textureColor.a != 0.0 && drawMode == 1)\r\n"
"	{\r\n"
"		int index = int(textureColor.r * 7.96875) * 3;\r\n"
"		gl_FragColor = (textureColor * vec4(colors[index], colors[index + 1], colors[index + 2], 1.0)) * 3.0;\r\n"
"	}\r\n"
"	else\r\n"
"		gl_FragColor = textureColor;\r\n"
"}";
//---------------------------------------------------------------------------
static const char *g_Frag_FontShaderData =
"uniform sampler2D usedTexture;\r\n"
"uniform int drawMode;\r\n"
"uniform float colors[96];\r\n"
"void main(void)\r\n"
"{\r\n"
"	vec4 textureColor = texture2D(usedTexture, gl_TexCoord[0].xy);\r\n"
"	if (textureColor.a != 0.0)\r\n"
"	{\r\n"
"		if (drawMode == 1 || (drawMode == 2 && textureColor.r == textureColor.g && textureColor.r == textureColor.b))\r\n"
"		{\r\n"
"			int index = int(textureColor.r * 31.875) * 3;\r\n"
"			gl_FragColor = vec4(colors[index], colors[index + 1], colors[index + 2], textureColor.a) * gl_Color;\r\n"
"		}\r\n"
"		else if (drawMode == 4 || (drawMode == 3 && textureColor.r > 0.04))\r\n"
"		{\r\n"
"			gl_FragColor = vec4(colors[90], colors[91], colors[92], textureColor.a) * gl_Color;\r\n"
"		}\r\n"
"		else\r\n"
"			gl_FragColor = textureColor * gl_Color;\r\n"
"	}\r\n"
"	else\r\n"
"		gl_FragColor = textureColor * gl_Color;\r\n"
"}";
//---------------------------------------------------------------------------
static const char *g_Frag_ColorizerShaderData =
"varying vec3 l;\r\n"
"varying vec3 n;\r\n"
"uniform sampler2D usedTexture;\r\n"
"uniform int drawMode;\r\n"
"uniform float colors[96];\r\n"
"void main(void)\r\n"
"{\r\n"
"	vec4 textureColor = texture2D(usedTexture, gl_TexCoord[0].xy);\r\n"
"	if (textureColor.a != 0.0)\r\n"
"	{\r\n"
"		if (drawMode == 1 || (drawMode == 2 && textureColor.r == textureColor.g && textureColor.r == textureColor.b))\r\n"
"		{\r\n"
"			int index = int(textureColor.r * 31.875) * 3;\r\n"
"			gl_FragColor = vec4(colors[index], colors[index + 1], colors[index + 2], textureColor.a) * gl_Color;\r\n"
"		}\r\n"
"		else if (drawMode > 5)\r\n"
"		{\r\n"
"			if (drawMode > 9)\r\n"
"			{\r\n"
"				float red = textureColor.r;\r\n"
"				if (drawMode > 10)\r\n"
"				{\r\n"
"					if (drawMode > 11)\r\n"
"						red = 0.6;\r\n"
"					else\r\n"
"						red *= 0.5;\r\n"
"				}\r\n"
"				else\r\n"
"					red *= 1.5;\r\n"
"				gl_FragColor = vec4(red, red, red, textureColor.a) * gl_Color;\r\n"
"			}\r\n"
"			else\r\n"
"			{\r\n"
"				vec3 n2 = normalize(n);\r\n"
"				vec3 l2 = normalize(l);\r\n"
"				vec4 normal = vec4(max(dot(n2, l2) + 0.5, 0.0));\r\n"
"				if (drawMode > 6)\r\n"
"				{\r\n"
"					int index = int(textureColor.r * 31.875) * 3;\r\n"
"					gl_FragColor = (vec4(colors[index], colors[index + 1], colors[index + 2], textureColor.a) * gl_Color) * normal;\r\n"
"				}\r\n"
"				else\r\n"
"					gl_FragColor = (textureColor * gl_Color) * normal;\r\n"
"			}\r\n"
"		}\r\n"
"		else\r\n"
"			gl_FragColor = textureColor * gl_Color;\r\n"
"	}\r\n"
"	else\r\n"
"		gl_FragColor = textureColor * gl_Color;\r\n"
"}";
//---------------------------------------------------------------------------
#endif