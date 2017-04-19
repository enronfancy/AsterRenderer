#pragma once

#include <math.h>
#include <string>
#include <sstream>
using namespace std;

class vector4
{
public:
	float v[4];

	vector4() { this->v[0] = this->v[1] = this->v[2] = this->v[3] = 0.0f; }

	vector4(float v0) { this->v[0] = this->v[1] = this->v[2] = this->v[3] = v0; }

	vector4(float v0, float v1, float v2, float v3)
	{
		this->v[0] = v0;
		this->v[1] = v1;
		this->v[2] = v2;
		this->v[3] = v3;
	}


	~vector4() {}

	float length()
	{
		return sqrt(this->sqrLength());
	}

	float sqrLength()
	{
		return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
	}

	vector4 neg()
	{
		return vector4(-v[0],-v[1],-v[2],-v[3]);
	}

	string str()
	{

		std::ostringstream ostr;
		ostr << "vector4[" << v[0] <<","<< v[1] <<","<< v[2] <<","<< v[3] <<"]";
		return ostr.str();
	}

	vector4 add(vector4& other)
	{
		return vector4(
			this->v[0] + other.v[0],
			this->v[1] + other.v[1],
			this->v[2] + other.v[2],
			this->v[3] + other.v[3]
			);
	}

	vector4 sub(vector4& other)
	{
		return this->add(other.neg());
	}

	vector4 mul(vector4& other)
	{
		return vector4(
			this->v[0] * other.v[0],
			this->v[1] * other.v[1],
			this->v[2] * other.v[2],
			this->v[3] * other.v[3]
		);
	}

	vector4 scale(float scale)
	{
		return vector4(
			this->v[0] * scale,
			this->v[1] * scale,
			this->v[2] * scale,
			this->v[3] * scale
		);
	}

	float dot(vector4& other)
	{
		return this->v[0] * other.v[0] +
			this->v[1] * other.v[1] +
			this->v[2] * other.v[2] +
			this->v[3] * other.v[3];
	}

	vector4 cross(vector4& other)
	{
		return vector4(
			this->v[1] * other.v[2] - this->v[2]* other.v[1],
			this->v[2] * other.v[0] - this->v[0]* other.v[2],
			this->v[0] * other.v[1] - this->v[1]* other.v[0],
			0.0f);
	}

	bool equal(vector4& other)
	{
		return this->v[0] == other.v[0] &&
			this->v[1] == other.v[1] &&
			this->v[2] == other.v[2] &&
			this->v[3] == other.v[3];
	}

	bool lenthEqual(vector4& other)
	{
		return this->sub(other).sqrLength() < 1e-10f;
	}

	vector4 normalize()
	{
		float l = length();
		if(!this->equalZero(l))
		{
			return vector4(
				this->v[0] / l,
				this->v[1] / l,
				this->v[2] / l,
				this->v[3] / l
				);
		}
		else 
			return vector4();
	}

	static bool equalZero(float v)
	{
		float epsilon = 1e-10f;
		return abs(v) < epsilon;
	}


	void set_x(float value)
	{
 		v[0] = value;
	}

	float get_x(){
		return v[0];
	}

	void set_y(float value)
	{
		v[1] = value;
	}

	float get_y(){
		return v[1];
	}

	void set_z(float value)
	{
		v[2] = value;
	}

	float get_z(){
		return v[2];
	}

	void set_w(float value)
	{
		v[3] = value;
	}

	float get_w(){
		return v[3];
	}

	__declspec( property( get = get_x, put = set_x ) )  float x; 
	__declspec( property( get = get_y, put = set_y ) )  float y; 
	__declspec( property( get = get_z, put = set_z ) )  float z; 
	__declspec( property( get = get_w, put = set_w ) )  float w; 
};