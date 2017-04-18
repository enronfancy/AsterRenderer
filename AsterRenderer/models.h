#pragma once

#include <array>
#include <memory>


class modelTriangle
{
public:
	std::array<int, 3> format;
	std::array<float, 24> vertices;
	
	modelTriangle()
	{
		std::array<int, 3> f = {3,3,2};
		std::memcpy(format.data(), f.data(), sizeof(int)*3);

		std::array<float, 24> v = 
		{
			0, 0, 0,	1, 0, 0,	0, 1,
			1, 0, 0,	0, 1, 0,	1, 1,
			0, 1, 0,	0, 0, 1,	0, 0,
		};
		std::memcpy(vertices.data(), v.data(), sizeof(float)* 24);
	}


};

class modelCube
{
public:
	std::array<int, 3> format;
	std::array<float, 288> vertices;

	modelCube()
	{
		std::array<int,3> f = {3,3,2};
		std::memcpy(format.data(), f.data(), sizeof(int)*3);

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

		std::memcpy(vertices.data(), v.data(), sizeof(float) * 288);
	}
};