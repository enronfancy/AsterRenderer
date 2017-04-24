#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include "glut.h"
#include "render.h"

using namespace std;

std::unique_ptr<renderer> p_renderer(new renderer());
unique_ptr<modelCube> p_triangle(new modelCube());

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
	glutCreateWindow("AsterRenderer! FPS:0");
}

void r(int id)
{ 
	auto start = clock();  
	p_renderer->rs->clearFrameBuffer();
	p_renderer->rs->clearDepthBuffer();

	auto clearBuffer = clock() - start;

	p_renderer->setupMatrices();

	auto matrices = clock() - start - clearBuffer;

	p_renderer->drawModel(p_triangle->format.data(), 
		p_triangle->format.size(), 
		p_triangle->vertices.data(),
		p_triangle->vertices.size(),
		1);

	auto draw = clock() - start - clearBuffer - matrices;

	glDrawPixels(p_renderer->rs->width, 
		p_renderer->rs->height, 
		GL_RGB, GL_UNSIGNED_BYTE, 
		p_renderer->rs->getFrameBuffer());
	glutSwapBuffers();

	auto swap = clock() - start - clearBuffer - matrices - draw;

	auto end = clock();  

	glutTimerFunc(0, r, 1);

	std::ostringstream ostr;
	auto totalTime = float(end - start);
	ostr << "AsterRenderer! FPS:" << int(1000.0 / totalTime ) <<", "<< int(clearBuffer/totalTime*100);
	ostr <<", "<< int(matrices/totalTime*100);
	ostr <<", "<< int(draw/totalTime*100);
	ostr <<", "<< int(swap/totalTime*100);

	glutSetIconTitle(ostr.str().c_str());
}

int main(int argc, char *argv[])
{
	//matrixTestCases();
	//vectorTestCases();
	
	initGLEnv(argc, argv);
	p_renderer->setupMatrices();
	p_renderer->drawModel(p_triangle->format.data(), 
		p_triangle->format.size(), 
		p_triangle->vertices.data(),
		p_triangle->vertices.size(), 2);
	
	glutDisplayFunc(setPixels);
	glutTimerFunc(0, r, 1);
	glutMainLoop();
}
