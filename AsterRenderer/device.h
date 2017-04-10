#pragma once

#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum RENDER_STATE
{
	RENDER_STATE_WIREFRAME = 1,		// 线框模式
	RENDER_STATE_TEXTURE = 2,		// 纹理模式
	RENDER_STATE_COLOR = 4			// 颜色模式
};


class Device
{
public:
	int width;
	int height;

	UINT32 **framebuffer;
	float **zbuffer;
	UINT32 **texture;

	int texWidth;
	int texHeight;

	RENDER_STATE render_state;

	UINT32 backgroudColor;
	UINT32 wireframeColor;

	Device(int _width, int _height)
	{
		this->width = _width;
		this->height = _height;

		// 指定渲染模式
		this->render_state = RENDER_STATE_WIREFRAME;

		int totalSize = sizeof(void*) * (height * 2 + 1024) + width * height * 8;
		char *ptr = (char*)malloc(totalSize + 64);
		this->framebuffer = (UINT32**)ptr;

		this->zbuffer = (float**)(ptr + sizeof(void*) * height);




	}

};