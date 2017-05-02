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
		auto normal = attributes[3];

		pos.w = 1;
		pos = rs->worldMatrix.transform(pos); // world
		pos = rs->viewMatrix.transform(pos); // view
		pos = rs->projectionMatrix.transform(pos); // projection
		pos = rs->viewportMatrix.transform(pos); // viewport


		normal = rs->worldMatrix.transform(normal); // world
		normal = rs->viewMatrix.transform(normal); // view
		normal = rs->projectionMatrix.transform(normal); // projection
		normal.w = 0;
		normal = normal.normalize();

		varyings.push_back(pos);
		varyings.push_back(color);
		varyings.push_back(uv);
		varyings.push_back(normal);

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

		finalPixel = vector4(r,g,b,1);

		// Lighting
		auto normal = varyings[3];
		auto lightDirection = vector4(-1,-1, -1, 0);
		lightDirection = lightDirection.normalize();

		auto lighting = max(0.2f, normal.dot(lightDirection));

		finalPixel = finalPixel.scale(lighting);

		return finalPixel;
	}

};