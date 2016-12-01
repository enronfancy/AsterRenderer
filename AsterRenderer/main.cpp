#include <iostream>
#include "glut.h"
#include <math.h>

using namespace std;

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

int main(int argc, char *argv[])
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
