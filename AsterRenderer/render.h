#pragma once
#include <memory>
#include <iostream>
#include "vector.h"
#include "shaders.h"
#include "matrix4.h"
#include "models.h"

typedef unsigned char byte;

#define RENDER_TYPE_WIREFRAME  0x1
#define RENDER_TYPE_SOLID 0x10

class vertexShader;
class pixelShader;

class renderState
{
public:
	std::unique_ptr<byte[]> frameBuffer;
	std::unique_ptr<byte[]> depthBuffer;
	unique_ptr<vertexShader> vs;
	unique_ptr<pixelShader> ps;
	matrix4 viewportMatrix;
	matrix4 viewMatrix;
	matrix4 worldMatrix;
	matrix4 projectionMatrix;
	int width, height;
	int renderType;

	renderState(int width, int height)
	{
		this->width = width;
		this->height = height;

		vs = unique_ptr<vertexShader>(new vertexShader());
		ps = unique_ptr<pixelShader>(new pixelShader());

		frameBuffer = std::unique_ptr<byte[]>(new byte[width * height * 3]);
		depthBuffer = std::unique_ptr<byte[]>(new byte[width * height]);

		viewportMatrix = matrix4::identity();
		viewMatrix = matrix4::identity();
		worldMatrix = matrix4::identity();
		projectionMatrix = matrix4::identity();

		this->clearFrameBuffer();
		this->clearDepthBuffer();

		renderType = RENDER_TYPE_WIREFRAME;
	}

	void clearFrameBuffer();
	void clearDepthBuffer();

	void* getFrameBuffer()
	{
		return frameBuffer.get();
	}
};


class renderer
{
public:
	std::unique_ptr<renderState> rs;

	renderer()
	{
		rs = std::unique_ptr<renderState>(new renderState(800, 600));
	}

	renderer(int width, int height)
	{
		rs = std::unique_ptr<renderState>(new renderState(width, height));
	}

	// Setup matrices
	void setupMatrices();

	// Draw a model
	void drawModel(int* const format, int formatNum, float* const vertices, int vertexNum);

	// Draw a triangle with 3 vertices
	void drawTriangle(vector<vector4> v1, vector<vector4> v2, vector<vector4> v3);

	// Draw a line on screen
	void drawLine(int x1, int x2, int y1, int y2, vector4 color, int radius = 1);

	// Draw a pixel
	void drawPixel(int x, int y, float z, byte r, byte g, byte b, int radius = 1);

	void drawSegment(vector<vector4>& v1, vector<vector4>& v2);
};