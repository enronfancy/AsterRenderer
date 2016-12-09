#pragma once

#include "definitions.h"

enum RENDER_STATE
{
	RENDER_STATE_WIREFRAME = 1,		// �߿�ģʽ
	RENDER_STATE_TEXTURE = 2,		// ����ģʽ
	RENDER_STATE_COLOR = 4			// ��ɫģʽ
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

		this->render_state = RENDER_STATE_WIREFRAME;
	}

};