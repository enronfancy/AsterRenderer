#include <iostream>
#include "glut.h"
#include <math.h>
#include "render.h"

using namespace std;
std::unique_ptr<renderer> p_renderer(new renderer());
unique_ptr<modelCube> p_triangle(new modelCube());

GLint width = 800;
GLint height = 600;
GLubyte* pixelData;

int colorIndex = 0;
int increment = 1;
long long counter = 0;

void display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	if (pixelData)
	{
		glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
	}

	glutSwapBuffers();
	//glFlush();
}


void initBuffer()
{
	GLint pixelLength = width* height * 3;
	pixelData = (GLubyte*)malloc(pixelLength);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pixelData[(i*width + j) * 3] = \
				pixelData[(i*width + j) * 3 + 1] = \
				pixelData[(i*width + j) * 3 + 2] = 0;
		}
	}
}

void wave(int id)
{

	if (pixelData)
	{

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				pixelData[(i*width + j) * 3]  = (int)( ((sin(counter*0.1) * 0.5) + 0.5) * 255 );
				pixelData[(i*width + j) * 3 + 1] = (int)(((sin(counter*0.05) * 0.5) + 0.5) * 255);;
				pixelData[(i*width + j) * 3 + 2] = (int)(((sin(counter*0.07) * 0.5) + 0.5) * 255);;
			}
		}
	}



	if (pixelData[0] >= 255 || pixelData[0] <= 0)
	{
		increment *= -1;
	}


	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

	glutSwapBuffers();
	//glFlush();

	glutTimerFunc(20, wave, 1);

	counter += 1;
}

void setPixels()
{
	glDrawPixels(p_renderer->rs->width, 
		p_renderer->rs->height, 
		GL_RGB, GL_UNSIGNED_BYTE, 
		p_renderer->rs->getFrameBuffer());
	glutSwapBuffers();
}

void printPixels(void* frameBuffer, int width, int height)
{
	auto size=  _msize(frameBuffer);
	cout<<"frame length:"<<size<<endl;
	for(auto i = 0; i < width; i ++)
	{
		for(auto j = 0; j < height; j ++)
		{
			auto res = static_cast<int>(static_cast<unsigned char*>(frameBuffer)[i*width + j]);
			cout<<res;
		}
		cout<<endl;
	}
}

void drawCase(int argc, char *argv[])
{
	initBuffer();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("AsterRenderer!");
	glutDisplayFunc(display);

	glutTimerFunc(20, wave, 1);

	glutMainLoop();
}

void vectorTestCases()
{
	vector4 v1(1,0,0,2);
	vector4 v2(1,2,3,4);

	cout<<"v2 len:" <<v2.length()<<endl;
	cout<<"v2 square len:" << v2.sqrLength()<<endl;
	cout<<"v2 neg:" << v2.neg().str()<<endl;
	cout<<"v2.normalize:"<<v2.normalize().str()<<endl;
	cout<<"v1 v2 add:"<< v1.add(v2).str()<<endl;
	cout<<"v1 v2 sub:"<< v1.sub(v2).str()<<endl;
	cout<<"v1 v2 mul:"<< v1.mul(v2).str()<<endl;
	cout<<"v2 scale:"<< v2.scale(2).str()<<endl;
	cout<<"v1 v2 dot:"<< v1.dot(v2)<<endl;
	cout<<"v1 v2 cross:"<< v1.cross(v2).str()<<endl;
	
	cout<<"v1, v2 equals:"<< v1.equal(v2)<<endl;
	cout<<"v1, v2 len equals:"<< v1.lenthEqual(v2)<<endl;
}

void matrixTestCases()
{
	auto m = matrix4().fromRows(
		vector4(1, 2, 0, 4),
		vector4(5, 1, 2, 8),
		vector4(1, 3, 4, 2),
		vector4(3, 1, 5, 9)
		);

	cout<< string ( "matrix4.getRow 2:\n" + m.getRow(2).str()) <<endl;
	cout<< string ( "matrix4.getCol 2:\n" + m.getCol(2).str()) <<endl;
	cout<< string ( "matrix4.transposed:\n" + m.tranpose().str() ) <<endl;
	cout<< string ( "matrix4.neg:\n" + m.neg().str()) <<endl;
	cout<< string ( "matrix4.add:\n" + m.add(m).str()) <<endl;
	cout<< string ( "matrix4.sub:\n" + m.sub(m).str()) <<endl;
	cout<< string ( "matrix4.elemMul:\n" + m.elemMul(m).str()) <<endl;
	cout<< string ( "matrix4.mul:\n" + m.mul(m).str()) <<endl;
	cout<< string ( "matrix4.scale 2:\n" + m.scale(2).str()) <<endl;
	cout<< string ( "matrix4.cofactor 1, 2:\n")<<m.cofactor(1, 2) <<endl;
	cout<< string ( "matrix4.det:\n") << m.det() <<endl;
	cout<< string ( "matrix4.invert:\n" + m.invert().str()) <<endl;
}

void initGLEnv(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(p_renderer->rs->width, p_renderer->rs->height);
	glutCreateWindow("AsterRenderer!");
}

void r(int id)
{ 
	p_renderer->rs->clearFrameBuffer();
	p_renderer->setupMatrices();
	p_renderer->drawModel(p_triangle->format.data(), 
		p_triangle->format.size(), 
		p_triangle->vertices.data(),
		p_triangle->vertices.size());

	glDrawPixels(p_renderer->rs->width, 
		p_renderer->rs->height, 
		GL_RGB, GL_UNSIGNED_BYTE, 
		p_renderer->rs->getFrameBuffer());
	glutSwapBuffers();

	glutTimerFunc(20, r, 1);
}

int main(int argc, char *argv[])
{
	//drawCase(argc, argv);
	//matrixTestCases();
	//vectorTestCases();
	
	initGLEnv(argc, argv);
	//p_renderer->drawLine(20, 700, 400, 200, vector4(255, 255, 0, 0), 1);

	p_renderer->setupMatrices();
	p_renderer->drawModel(p_triangle->format.data(), 
		p_triangle->format.size(), 
		p_triangle->vertices.data(),
		p_triangle->vertices.size());
	
	glutDisplayFunc(setPixels);
	glutTimerFunc(20, r, 1);
	glutMainLoop();
}
