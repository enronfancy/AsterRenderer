#pragma once
#include <memory>
#include <string>
#include <fstream>
#include "definitions.h"
using namespace std;

class texture
{
public:
	BYTE* data;
	int width;
	int height;
	texture(){};
	~texture(){delete data;}

	BYTE get_r(int x, int y)
	{
		return *(data+ (y * width + x) * 4+2);
	}

	BYTE get_b(int x, int y)
	{
		return *(data+ (y * width + x) * 4 + 0);
	}

	BYTE get_g(int x, int y)
	{
		return *(data+ (y * width + x) * 4 + 1);
	}

	void loadTex(string filename)
	{
		ifstream tgafile(filename, ios::binary);
		if (!tgafile)
			return;

		// The image header
		unsigned char header[18] = { 0 };
		tgafile.read(reinterpret_cast<char*>(header), sizeof(header));
		int w = (header[13] << 8) | header[12];
		int h = (header[15] << 8) | header[14];
		int bits = header[16];

		this->width = w;
		this->height = h;
		this->data = new BYTE[width*height*4];

		if (header[17] & 0x20)
		{
			for (int y = 0; y < height; y++)
				for (int x = 0; x < width; x++)
				{
					auto pixel = data + (y*width+x)*4;
					if (bits == 32)
						tgafile.read(reinterpret_cast<char*>(pixel), 4);
					else if (bits == 24)
					{
						tgafile.read(reinterpret_cast<char*>(pixel), 3);
						pixel[3] = 0;
					}
					else
						throw runtime_error("Wrong tga format");
				}
		}
		else
		{
			for (int y = height - 1; y >= 0; y--)
				for (int x = 0; x < width; x++)
				{
					auto pixel = data + (y*width+x)*4;
					if (bits == 32)
						tgafile.read(reinterpret_cast<char*>(pixel), 4);
					else if (bits == 24)
					{
						tgafile.read(reinterpret_cast<char*>(pixel), 3);
						pixel[3] = 0;
					}
					else
						throw runtime_error("Wrong tga format");
				}
		}
	}

	
};