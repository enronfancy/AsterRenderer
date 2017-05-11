#pragma once

#include <array>
#include <memory>
#include "definitions.h"


class model
{
public:
	vector<int> format;
	int modelType;
};

class modelTriangle:public model
{
public:
	vector<float> vertices;
	int vertexNum;

	modelTriangle()
	{
		std::array<int, 3> f = {3,3,2};
		for(auto i = 0; i < 3; i++)
		{
			format.push_back(f[i]);
		}

		vertexNum = 24;
		
		std::array<float, 24> v = 
		{
			0, 0, 0,	1, 0, 0,	0, 1,
				1, 0, 0,	0, 1, 0,	1, 1,
				0, 1, 0,	0, 0, 1,	0, 0,
		};
		
		for(auto i = 0; i < 24; i++)
		{
			vertices.push_back(v[i]);
		}
	}

};

class modelCube:public model
{
public:
	vector<float> vertices;
	int vertexNum;

	modelCube()
	{
		std::array<int,3> f = {3,3,2};
		for(auto i = 0; i < 3; i++)
		{
			format.push_back(f[i]);
		}

		vertexNum = 288;
		std::array<float, 288> v = 
		{
			-1.0, 1.0, 1.0,		1, 0, 0,	0, 1,
			1.0, 1.0, 1.0,		0, 1, 0,	1, 1,
			1.0, 1.0, -1.0,		0, 0, 1,	1, 0,
			-1.0, 1.0, 1.0,		1, 0, 0,	0, 1,
			1.0, 1.0, -1.0,		0, 0, 1,	1, 0,
			-1.0, 1.0, -1.0,	1, 1, 0,	0, 0,

			-1.0, -1.0, 1.0,	0, 0, 1,	0, 0,
			-1.0, -1.0, -1.0,	0, 1, 0,	0, 1,
			1.0, -1.0, -1.0,	1, 0, 0,	1, 1,
			-1.0, -1.0, 1.0,	0, 0, 1,	0, 0,
			1.0, -1.0, -1.0,	1, 0, 0,	1, 1,
			1.0, -1.0, 1.0,		1, 0, 1,	1, 0,

			-1.0, -1.0, -1.0,	0, 1, 0,	0, 1,
			-1.0, -1.0, 1.0,	1, 0, 0,	1, 1,
			-1.0, 1.0, 1.0,		0, 0, 1,	1, 0,
			-1.0, -1.0, -1.0,	0, 1, 0,	0, 1,
			-1.0, 1.0, 1.0,		0, 0, 1,	1, 0,
			-1.0, 1.0, -1.0,	1, 1, 1,	0, 0,

			1.0, -1.0, -1.0,	1, 0, 1,	1, 1,
			1.0, 1.0, -1.0,		0, 1, 0,	1, 0,
			1.0, 1.0, 1.0,		1, 1, 1,	0, 0,
			1.0, -1.0, -1.0,	1, 0, 1,	1, 1,
			1.0, 1.0, 1.0,		1, 1, 1,	0, 0,
			1.0, -1.0, 1.0,		0, 0, 1,	0, 1,

			-1.0, -1.0, -1.0,	1, 0, 0,	1, 1,
			-1.0, 1.0, -1.0,	0, 0, 1,	1, 0,
			1.0, 1.0, -1.0,		1, 0, 1,	0, 0,
			-1.0, -1.0, -1.0,	1, 0, 0,	1, 1,
			1.0, 1.0, -1.0,		1, 0, 1,	0, 0,
			1.0, -1.0, -1.0,	0, 1, 0,	0, 1,

			-1.0, -1.0, 1.0,	0, 1, 0,	0, 1,
			1.0, -1.0, 1.0,		1, 0, 1,	1, 1,
			1.0, 1.0, 1.0,		0, 1, 1,	1, 0,
			-1.0, -1.0, 1.0,	0, 1, 0,	0, 1,
			1.0, 1.0, 1.0,		0, 1, 1,	1, 0,
			-1.0, 1.0, 1.0,		1, 0, 0,	0, 0,
		};

		for(auto i = 0; i < 288; i++)
		{
			vertices.push_back(v[i]);
		}
	}
	
};

class customModel: public model
{
public:
	std::vector<float> vertices;
	int vertexNum;

	customModel()
	{
	}

	void setVertices(vector<float> vertices, int vertexNum)
	{
		this->vertices = vertices;
		this->vertexNum = vertexNum;
	}


};