#pragma once

#include <math.h>
#include "vector.h"

class matrix4 {
private:
	float m[4][4];

public:
	matrix4()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = 0.0f;
			}
		}
	}

	matrix4(float scale)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
				{
					m[i][j] = scale;
				}
				else
				{
					m[i][j] = 0.0f;
				}
			}
		}
	}

	static matrix4 identity()
	{
		return matrix4(1.0f);
	}

	void tranpose()
	{

	}


};