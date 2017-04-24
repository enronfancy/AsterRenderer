#pragma once
#include <memory>
#include "definitions.h"
#include "texture.h"
#include "utility.h"

#define RENDER_TYPE_WIREFRAME  (0x1)
#define RENDER_TYPE_SOLID (0x1<<1)

#define MAX_TEXTURES 4

class renderState
{
public:
	std::unique_ptr<BYTE[]> frameBuffer;
	std::unique_ptr<float[]> depthBuffer;
	matrix4 viewportMatrix;
	matrix4 viewMatrix;
	matrix4 worldMatrix;
	matrix4 projectionMatrix;
	int width, height;
	int renderType;
	unique_ptr<texture> tex;

	renderState(int width, int height)
	{
		this->width = width;
		this->height = height;

		frameBuffer = std::unique_ptr<BYTE[]>(new BYTE[width * height * 3]);
		depthBuffer = std::unique_ptr<float[]>(new float[width * height]);

		viewportMatrix = matrix4::identity();
		viewMatrix = matrix4::identity();
		worldMatrix = matrix4::identity();
		projectionMatrix = matrix4::identity();

		this->clearFrameBuffer();
		this->clearDepthBuffer();

		tex = unique_ptr<texture>(new texture()) ;
		tex->loadTex("lsj.tga");
		renderType = RENDER_TYPE_SOLID;
	}
	
	~renderState()
	{
	}

	void clearFrameBuffer()
	{
		memset(this->frameBuffer.get(), 0, width*height*sizeof(BYTE)*3);
	}
	void clearDepthBuffer()
	{
		for(auto i = 0; i < width * height; ++i)
		{
			this->depthBuffer[i] = 1.0f;
		}
	}

	void* getFrameBuffer()
	{
		return frameBuffer.get();
	}

	bool createTexture(string texFileName, int textureIndex =  0)
	{
		return true;
	}

	


};
