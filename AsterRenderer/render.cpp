#include "render.h"
#include <math.h>
#include "utility.h"
#include <iostream>
#include "definitions.h"

int counter = 0;
void renderer::setupMatrices()
{
	this->rs->viewportMatrix = matrix4::viewport(this->rs->width, this->rs->height, 0.0f, 1.0f);
	this->rs->worldMatrix = matrix4::fromRotationY(counter/50.0f);
	counter++;

	//cout<<"counter:"<<counter<<endl;

	this->rs->viewMatrix = matrix4::lookAt(
		vector4(0, 1.2, 2.5, 1), // eye
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
			drawPixel(y, i, 0.0f, static_cast<BYTE>(color.x), static_cast<BYTE>(color.y), static_cast<BYTE>(color.z), radius);
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
			drawPixel(i, x, 0.0f, static_cast<BYTE>(color.x), static_cast<BYTE>(color.y), static_cast<BYTE>(color.z), radius);

			eps += dx;
			if(eps*2 >= dy)
			{
				x += ux;
				eps -= dy;
			}
		}
	}

}

void renderer::drawSegment(vector<vector4>& v1, vector<vector4>& v2, int radius)
{
	auto x1 = v1[0].x / v1[0].w;
	auto y1 = v1[0].y / v1[0].w;	
	auto x2 = v2[0].x / v2[0].w;
	auto y2 = v2[0].y / v2[0].w;
	
	this->drawLine(
		int(x1 + 0.5f), 
		int(x2 + 0.5f), 
		int(y1 + 0.5f), 
		int(y2 + 0.5f),
		vector4(255,255,0,0),
		radius);
}

void renderer::drawPixel(int x, int y, float z, BYTE r, BYTE g, BYTE b, int radius)
{
	//TODO: Depth test
	auto depthIndex =  x* this->rs->width + y;
	auto currentDepth =this->rs->depthBuffer[depthIndex];

	if(z < currentDepth)
	{
		this->rs->depthBuffer[depthIndex] = z;
	
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

}

void renderer::drawTriangle(vector<vector4>& v1, vector<vector4>& v2, vector<vector4>& v3)
{
	// Homogenize coordinates
	auto w1 = v1[0].w, w2 = v2[0].w, w3 = v3[0].w;

	auto pos_1 = v1[0].scale(1.0f/w1);
	auto pos_2 = v2[0].scale(1.0f/w2);
	auto pos_3 = v3[0].scale(1.0f/w3);

	auto minX = min(pos_1.x, min(pos_2.x, pos_3.x));
	auto maxX = max(pos_1.x, max(pos_2.x, pos_3.x));
	auto minY = min(pos_1.y, min(pos_2.y, pos_3.y));
	auto maxY = max(pos_1.y, max(pos_2.y, pos_3.y));

	auto varyingCount = v1.size();

	auto f12 = [&pos_1, &pos_2](float x,float y){
		return (pos_1.y - pos_2.y) * x
			+ (pos_2.x - pos_1.x) * y
			+ pos_1.x * pos_2.y - pos_2.x * pos_1.y;
	};

	auto f23 = [&pos_2, &pos_3](float x,float y){
		return (pos_2.y - pos_3.y) * x
			+ (pos_3.x - pos_2.x) * y
			+ pos_2.x * pos_3.y - pos_3.x * pos_2.y;
	};

	auto f31 = [&pos_1,&pos_3](float x,float y){
		float res = 0.0f;
		auto a1 = (pos_3.y - pos_1.y) * x;
		auto a2 = (pos_1.x - pos_3.x) * y;
		auto a3 = pos_3.x * pos_1.y - pos_1.x * pos_3.y;

		res = a1 + a2 + a3;
		return a1 + a2 + a3;
	};


	auto startX = floorf(minX), startY = floorf(minY);
	auto endX = ceilf(maxX), endY = ceilf(maxY);

	for(auto i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			auto alpha = f23(j, i) / f23(pos_1.x, pos_1.y);
			auto beta = f31(j, i) / f31(pos_2.x, pos_2.y);
			auto gamma = f12(j, i) / f12(pos_3.x, pos_3.y);

			if(alpha > 0 && beta > 0 && gamma > 0)
			{
				auto perspectCorrector = alpha / w1 + beta / w2 + gamma / w3;
				vector<vector4> varyings;
				for(auto k = 0; k < varyingCount; k++)
				{
					auto varying = v1[k].scale(alpha/w1).add(v2[k].scale(beta/w2).add(v3[k].scale(gamma/w3)));

					varying = varying.scale(1.0f / perspectCorrector);

					varyings.push_back(varying);
				}
				auto color = this->ps->processPixel(varyings, this->rs);

				drawPixel(i, j, varyings[0].z / varyings[0].w, color.x, color.y, color.z);
			}
		}
	}

}

void renderer::drawModel(int* const format, int formatNum, float* const vertices, int vertexNum, int radius)
{
	bool renderWireframe = static_cast<bool>(this->rs->renderType & 0x1);
	bool renderSolid = static_cast<bool>(this->rs->renderType>>1 & 0x1);

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

		processedVertexBuffer.push_back( this->vs->processVertex(attributes, this->rs)); 

	}

	auto triangleCount = vertexCount / 3;


	// Draw wire frame
	if(renderWireframe)
	{
		for(auto triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++)
		{
			auto v1 = processedVertexBuffer[triangleIndex*3];
			auto v2 = processedVertexBuffer[triangleIndex*3+1];
			auto v3 = processedVertexBuffer[triangleIndex*3+2];

			this->drawSegment(v1, v2, radius);
			this->drawSegment(v1, v3, radius);
			this->drawSegment(v2, v3, radius);
		}
	}

	// Draw solid geometry
	if(renderSolid)
	{
		for(auto triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++)
		{
			auto v1 = processedVertexBuffer[triangleIndex*3];
			auto v2 = processedVertexBuffer[triangleIndex*3+1];
			auto v3 = processedVertexBuffer[triangleIndex*3+2];

			this->drawTriangle(v1, v2, v3);
		}
	}
}