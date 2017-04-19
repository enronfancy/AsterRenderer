#pragma once

#include <vector>
#include "vector.h"
#include "matrix4.h"

class vertexShader
{
public:
	virtual vector<vector4> processVertex(vector<vector4>& attributes, vector<matrix4>& matrices)
	{
		vector<vector4> varyings;

		auto pos = attributes[0];
		auto color = attributes[1];
		auto uv = attributes[2];

		pos.w = 1;
		pos = matrices[0].transform(pos); // world
		pos = matrices[1].transform(pos); // view
		pos = matrices[2].transform(pos); // projection
		//pos = matrices[3].transform(pos); // viewport

		varyings.push_back(pos);
		varyings.push_back(color);
		varyings.push_back(uv);

		return varyings;
	}
};

class pixelShader
{
public:
	virtual vector4 processPixel(vector<vector4>& varyings)
	{
		vector4 finalPixel;


		return finalPixel;
	}

};