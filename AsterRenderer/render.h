#pragma once
#include <memory>
#include <iostream>
#include "vector.h"
#include "shaders.h"
#include "matrix4.h"
#include "models.h"
#include "renderState.h"


class renderer
{
public:
	std::unique_ptr<renderState> rs;
	unique_ptr<vertexShader> vs;
	unique_ptr<pixelShader> ps;

	renderer()
	{
		rs = std::unique_ptr<renderState>(new renderState(800, 600));
		vs = unique_ptr<vertexShader>(new vertexShader());
		ps = unique_ptr<pixelShader>(new pixelShader());
	}

	renderer(int width, int height)
	{
		rs = std::unique_ptr<renderState>(new renderState(width, height));
		vs = unique_ptr<vertexShader>(new vertexShader());
		ps = unique_ptr<pixelShader>(new pixelShader());
	}

	// Setup matrices
	void setupMatrices();

	// Draw a model
	void drawModel(int* const format, int formatNum, float* const vertices, int vertexNum, int radius = 1);

	// Draw a triangle with 3 vertices
	void drawTriangle(vector<vector4>& v1, vector<vector4>& v2, vector<vector4>& v3);

	// Draw a line on screen
	void drawLine(int x1, int x2, int y1, int y2, vector4 color, int radius = 1);

	// Draw a pixel
	void drawPixel(int x, int y, float z, BYTE r, BYTE g, BYTE b, int radius = 1);

	void drawSegment(vector<vector4>& v1, vector<vector4>& v2, int radius = 1);
};