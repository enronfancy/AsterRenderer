#pragma once

#include <vector>
#include "vector.h"
#include "matrix4.h"
#include "renderState.h"

class vertexShader
{
public:
	virtual vector<vector4> processVertex(vector<vector4>& attributes, unique_ptr<renderState>& rs)
	{
		vector<vector4> varyings;

		auto pos = attributes[0];
		auto color = attributes[1];
		auto uv = attributes[2];

		pos.w = 1;
		pos = rs->worldMatrix.transform(pos); // world
		pos = rs->viewMatrix.transform(pos); // view
		pos = rs->projectionMatrix.transform(pos); // projection
		pos = rs->viewportMatrix.transform(pos); // viewport

		varyings.push_back(pos);
		varyings.push_back(color);
		varyings.push_back(uv);

		return varyings;
	}
};

class pixelShader
{
public:
	virtual vector4 processPixel(vector<vector4>& varyings, unique_ptr<renderState>& rs)
	{
		vector4 finalPixel;

		finalPixel = varyings[1].scale(255.0f);

		auto uv = varyings[2];
		auto tex = rs->tex.get();

		auto u = static_cast<int>((uv.x * tex->width + 0.5));
		auto v = static_cast<int>((uv.y * tex->height + 0.5));
		auto r = tex->get_r(u,v);
		auto b = tex->get_b(u,v);
		auto g = tex->get_g(u,v);

		finalPixel = (vector4(r,g,b,0));
		return finalPixel;
	}

};