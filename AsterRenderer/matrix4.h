#pragma once

#include <math.h>
#include <string>
#include <array>
#include "vector.h"
using namespace std;

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
				if (i == j && i != 3)
				{
					m[i][j] = scale;
				}
				else{
					m[i][j] = 0.0f;
				}
			}
		}

		m[3][3] = 1.0f;
	}

	matrix4(matrix4& other)
	{
		for(int i = 0; i <4; i ++)
		{
			for(int j = 0; j < 4; j++)
			{
				m[i][j] = other.m[i][j];
			}
		}
	}

	static matrix4 identity()
	{
		return matrix4(1.0f);
	}

	matrix4 tranpose()
	{
		auto result = matrix4();

		for(int i =0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[j][i];
			}
		}
		return result;
	}

	static matrix4 fromRows(vector4 v1, vector4 v2, vector4 v3, vector4 v4)
	{
		auto result = matrix4();
		result.m[0][0] = v1.x;  result.m[0][1] = v1.y; result.m[0][2] = v1.z; result.m[0][3] = v1.w;
		result.m[1][0] = v2.x;  result.m[1][1] = v2.y; result.m[1][2] = v2.z; result.m[1][3] = v2.w;
		result.m[2][0] = v3.x;  result.m[2][1] = v3.y; result.m[2][2] = v3.z; result.m[2][3] = v3.w;
		result.m[3][0] = v4.x;  result.m[3][1] = v4.y; result.m[3][2] = v4.z; result.m[3][3] = v4.w;
		return result;
	}

	static matrix4 fromCols(vector4 v1, vector4 v2, vector4 v3, vector4 v4)
	{
		return fromRows(v1, v2, v3, v4).tranpose();
	}

	static matrix4 fromTranslation(vector4 v)
	{
		auto result = matrix4::identity();
		result.m[0][3] = v.x;
		result.m[1][3] = v.y;
		result.m[2][3] = v.z;
		return result;
	}

	static matrix4 fromRotationX(float angle)
	{
		auto result = matrix4::identity();
		result.m[1][1] = cos(angle);
		result.m[1][2] = -sin(angle);
		result.m[2][1] = sin(angle);
		result.m[2][2] = cos(angle);
		return result;
	}

	static matrix4 fromRotationY(float angle)
	{
		auto result = matrix4::identity();
		result.m[0][0] = cos(angle);
		result.m[0][2] = sin(angle);
		result.m[2][0] = -sin(angle);
		result.m[2][2] = cos(angle);
		return result;
	}

	static matrix4 fromRotationZ(float angle)
	{
		auto result = matrix4::identity();
		result.m[0][0] = cos(angle);
		result.m[0][1] = -sin(angle);
		result.m[1][0] = sin(angle);
		result.m[1][1] = cos(angle);
	}

	void set(int row, int col, float value)
	{
		m[row][col] = value;
	}

	void set(float v0,float v1,float v2,float v3,
		float v4,float v5,float v6,float v7,
		float v8,float v9,float v10,float v11,
		float v12,float v13, float v14, float v15)
	{
		m[0][0] = v0;   m[0][1] = v1; m[0][2] = v2; m[0][3] = v3;
		m[1][0] = v4;   m[1][1] = v5; m[1][2] = v6; m[1][3] = v7;
		m[2][0] = v8;   m[2][1] = v9; m[2][2] = v10; m[2][3] = v11;
		m[3][0] = v12;   m[3][1] = v13; m[3][2] = v14; m[3][3] = v15;
	}

	float get(int row, int col)
	{
		return m[row][col];
	}

	vector4 getRow(int row)
	{
		return vector4(m[row][0],m[row][1],m[row][2],m[row][3]);
	}

	vector4 getCol(int col)
	{
		return vector4(m[0][col],m[1][col],m[2][col],m[3][col]);
	}

	matrix4 neg()
	{
		auto result = matrix4();
		for(int i = 0; i <4; i ++)
		{
			for(int j = 0; j < 4; j++)
			{
				result.m[i][j] = -m[i][j];
			}
		}
		return result;
	}

	matrix4 add(matrix4& other)
	{
		auto result = matrix4();
		for(int i = 0; i <4; i ++)
		{
			for(int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[i][j] + other.m[i][j];
			}
		}
		return result;
	}

	matrix4 sub(matrix4& other)
	{
		return add(other.neg());
	}

	matrix4 elemMul(matrix4& other)
	{
		auto result = matrix4();
		for(int i = 0; i <4; i ++)
		{
			for(int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[i][j] * other.m[i][j];
			}
		}
		return result;
	}

	matrix4 mul(matrix4& other)
	{
		auto result = matrix4::identity();
		for(auto i = 0; i < 4; ++i)
		{
			for(auto j = 0; j < 4; ++j)
			{
				result.set(i, j, getRow(i).dot(other.getCol(j)));
			}
		}
		return result;
	}

	matrix4 scale(float s)
	{
		auto result = matrix4();
		for(int i = 0; i <4; i ++)
		{
			for(int j = 0; j < 4; j++)
			{
				result.m[i][j] = s * m[i][j];
			}
		}
		return result;
	}

	float cofactor(int row, int col)
	{
		auto sign = (row + col) % 2 == 0 ? 1 : -1;
		auto remainMat = array<float, 9>();

		for(auto i = 0, srcRow = 0; i < 3; ++srcRow)
		{
			if(srcRow == row) continue;

			for(auto j = 0, srcCol = 0; j < 3; ++srcCol)
			{
				if(srcCol == col) continue;

				remainMat[i*3 + j] = get(srcRow, srcCol);
				++j;
			}
			++i;
		}

		auto remainMatDet = remainMat[0]* remainMat[4] *  remainMat[8]
		+ remainMat[2]* remainMat[3] *  remainMat[7]
		+ remainMat[6]* remainMat[1] *  remainMat[5]
		- remainMat[2]* remainMat[4] *  remainMat[6]
		- remainMat[0]* remainMat[5] *  remainMat[7]
		- remainMat[8]* remainMat[3] *  remainMat[1];

		return sign * remainMatDet;
	}

	float det()
	{
		auto result = 0.0f;
		for(auto i = 0; i < 4; ++i)
		{
			result += this->get(i, 0) * cofactor(i, 0);
		}
		return result;
	}

	matrix4 invert()
	{
		auto result = matrix4();

		for(int i = 0; i <4; i ++)
		{
			for(int j = 0; j < 4; j++)
			{
				result.set(i,j, cofactor(i, j));
			}
		}
		auto cofactorMatrix = result.tranpose();
		return cofactorMatrix.scale( 1.0f / this->det());
	}

	string str()
	{
		std::ostringstream ostr;
		ostr << "matrix4:[" << m[0][0] <<"\t"<< m[0][1] <<"\t"<< m[0][2] <<"\t"<< m[0][3] << "\n ";
		ostr << "        " << m[1][0] <<"\t"<< m[1][1] <<"\t"<< m[1][2] <<"\t"<< m[1][3] << "\n ";
		ostr << "        " << m[2][0] <<"\t"<< m[2][1] <<"\t"<< m[2][2] <<"\t"<< m[2][3] << "\n ";
		ostr << "        " << m[3][0] <<"\t"<< m[3][1] <<"\t"<< m[3][2] <<"\t"<< m[3][3] << "]\n";
		return ostr.str();
	}

	static matrix4 lookAt(vector4 eye, vector4 at, vector4 up)
	{
		auto w = at.sub(eye).normalize().neg();
		auto u = up.cross(w).normalize();
		auto v = w.cross(u);

		return matrix4().fromCols(u,v, w, eye).invert();
	}

	static matrix4 viewport(float nx, float ny, float near, float far)
	{
		auto result = matrix4::identity();

		result.set( nx / 2.0f, 0, 0, (nx - 1.0f) / 2.0f,
			0, ny / 2.0f, 0, (ny - 1.0f) / 2.0f,
			0, 0, (far - near) / 2.0f, (far + near) / 2.0f,
			0, 0, 0, 1.0f
			);
		return result;
	}

	static matrix4 perspective(float fovy, float aspect, float near, float far)
	{
		auto f = 1.0f / tan(fovy / 2.0f);
		auto nf = 1 / (near - far);

		auto result = matrix4::identity();
		result.set(
			f / aspect, 0, 0, 0,
			0, f, 0, 0,
			0, 0, (far + near) * nf, (2.0f * far * near) * nf,
			0, 0, -1.0f, 0
			);
		return result;
	}

	vector4 transform(vector4 v)
	{
		auto result = vector4();

		for(auto i = 0; i < 4; ++i)
		{
			result.v[i] = result.dot(this->getRow(i));
		}
		return result;
	}

};