#include "render.h"
#include <math.h>
#include "utility.h"
#include <iostream>

#define PI 3.1415927

void renderState::clearFrameBuffer()
{
	for(auto i = 0; i < width * height * 3; ++i)
	{
		this->frameBuffer[i] = 0;
	}
}

void renderState::clearDepthBuffer()
{
	for(auto i = 0; i < width * height; ++i)
	{
		this->depthBuffer[i] = 0;
	}
}

int counter = 0;
void renderer::setupMatrices()
{
	this->rs->viewportMatrix = matrix4::viewport(this->rs->width, this->rs->height, 0, 1);
	this->rs->worldMatrix = matrix4::fromRotationY(counter/10.0f);
	counter++;

	//cout<<"counter:"<<counter<<endl;

	this->rs->viewMatrix = matrix4::lookAt(
		vector4(0, 2, 3.5, 1), // eye
		vector4(0, 0, 0, 1), // at
		vector4(0, 1, 0, 0) // up
		);
	this->rs->projectionMatrix = matrix4::perspective(PI / 2.0f, // fov
		static_cast<float>(this->rs->width) / static_cast<float>(this->rs->height), // aspect
		1.0f, // near
		100.0f // far
		);
}


void renderer::drawLine(int x1, int x2, int y1, int y2, vector4 color, int radius)
{
	auto dx = x2 - x1;
	auto dy = y2 - y1;

	auto ux = x2 > x1 ? 1 : -1;
	auto uy = y2 > y1 ? 1 : -1;

	auto x = x1, y = y1, eps = 0;
	dx = abs(dx);
	dy = abs(dy);

	if(dx > dy)
	{
		for(auto i = x1; inRange(i, x1, x2, ux); i += ux)
		{
			drawPixel(y, i, 0.0f, static_cast<byte>(color.x), static_cast<byte>(color.y), static_cast<byte>(color.z), radius);
			eps += dy;

			if(eps* 2 >= dx)
			{
				y += uy;
				eps -= dx;
			}
		}
	}
	else
	{
		for(auto i = y1; inRange(i, y1, y2, uy); i += uy)
		{
			drawPixel(i, x, 0.0f, static_cast<byte>(color.x), static_cast<byte>(color.y), static_cast<byte>(color.z), radius);

			eps += dx;
			if(eps*2 >= dy)
			{
				x += ux;
				eps -= dy;
			}
		}
	}

}

void renderer::drawSegment(vector<vector4>& v1, vector<vector4>& v2)
{
	auto x1 = v1[0].x / v1[0].w;
	x1 = (x1 + 1.0) / 2.0 * this->rs->width;
	auto y1 = v1[0].y / v1[0].w;
	y1 = (y1 + 1.0) / 2.0 * this->rs->height;
	auto x2 = v2[0].x / v2[0].w;
	x2 = (x2 + 1.0) / 2.0 * this->rs->width;
	auto y2 = v2[0].y / v2[0].w;
	y2 = (y2 + 1.0) / 2.0 * this->rs->height;

	this->drawLine(
		int(x1 + 0.5f), 
		int(x2 + 0.5f), 
		int(y1 + 0.5f), 
		int(y2 + 0.5f),
		vector4(255,255,0,0),
		1);
}

void renderer::drawPixel(int x, int y, float z, byte r, byte g, byte b, int radius)
{
	//TODO: Depth test

	for(auto i = x - radius/2; i <= x + radius/2; i++)
	{
		for(auto j = y - radius/2; j <= y + radius/2; j++)
		{
			if( i < 0 || i >= this->rs->height) continue;
			if( j < 0 || j >= this->rs->width) continue;

			//cout<<"Draw pixel:"<<j<<" "<<i<<endl;
			this->rs->frameBuffer[(i* this->rs->width + j)*3] = r;
			this->rs->frameBuffer[(i* this->rs->width + j)*3+ 1] = g;
			this->rs->frameBuffer[(i* this->rs->width + j)*3 + 2] = b;
		}
	}

}

void renderer::drawTriangle(vector<vector4> v1, vector<vector4> v2, vector<vector4> v3)
{

}

void renderer::drawModel(int* const format, int formatNum, float* const vertices, int vertexNum)
{
	bool renderWireframe = static_cast<bool>(this->rs->renderType && 0x1);
	bool renderSolid = static_cast<bool>(this->rs->renderType>>1 && 0x1);

	int vertexSize = 0;
	for(auto i = 0; i < formatNum; i++)
	{
		vertexSize += format[i];
	}
	auto vertexCount = vertexNum / vertexSize;

	// Create buffer for processed vertices
	vector<vector<vector4>> processedVertexBuffer;
	vector<matrix4> matrices;
	matrices.push_back(this->rs->worldMatrix.clone());
	matrices.push_back(this->rs->viewMatrix.clone());
	matrices.push_back(this->rs->projectionMatrix.clone());
	matrices.push_back(this->rs->viewportMatrix.clone());

	// Process every vertex
	for(auto vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
	{
		vector<vector4> attributes;

		// Convert vertex data to attributes
		for(auto attributeIndex = 0, bufferIndex = 0; attributeIndex < formatNum; attributeIndex++)
		{
			vector4 attribute;
			for(auto i = 0; i < format[attributeIndex]; i++)
			{
				attribute.v[i] = vertices[vertexIndex * vertexSize + bufferIndex];
				++ bufferIndex;
			}
			attributes.push_back(attribute);
		}

		processedVertexBuffer.push_back( this->rs->vs->processVertex(attributes, matrices)); 

	}

	auto triangleCount = vertexCount / 3;


	// Render wire frame
	if(renderWireframe)
	{
		for(auto triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++)
		{
			auto v1 = processedVertexBuffer[triangleIndex*3];
			auto v2 = processedVertexBuffer[triangleIndex*3+1];
			auto v3 = processedVertexBuffer[triangleIndex*3+2];

			this->drawSegment(v1, v2);
			this->drawSegment(v1, v3);
			this->drawSegment(v2, v3);
		}
	}

	// Render solid geometry
	if(renderSolid)
	{

	}
}