// gutwindow.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <iostream>
#include <math.h>

#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"

#include "Functions.h"

using namespace std;
float angle = 0.0;           // global var, rotating angle of the teapot

SphereChanger SizeChange;
void KeyListener(unsigned char Key, int x, int y);
void idle();
void display();
void reshape(int w, int h);  // w is the width of the reshaped window
							 // h is the height of the reshaped window

int main(int argc, char ** argv)
{
	// initialize glut
	glutInit(&argc, argv);

	// initialize glut window
	glutInitWindowPosition(10, 10);

	// initialize window size
	glutInitWindowSize(640, 480);

	// display mode
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// create a window
	glutCreateWindow("Tracing Ray");

	// register the display function
	glutDisplayFunc(display);

	glutIdleFunc(idle);

	// Keyboard event handler
	glutKeyboardFunc(KeyListener);


	// register the reshape function
	glutReshapeFunc(reshape);
	// glut processing loop
	glutMainLoop();

	return 0;
}

void idle()
{
	glutPostRedisplay();
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Setup();
	Point first_pixel;

	first_pixel.x = -0.5 * screen.width;
	first_pixel.y = 0.5 * screen.height;
	first_pixel.z = screen.z;
	
	float delta_X, delta_Y;
	delta_X = screen.width / screen.x;
	delta_Y = screen.height / screen.y;

	int no_of_scanlines = screen.y;
	int no_of_pixels = screen.x;

	Point pixel;
	pixel.x = first_pixel.x;
	pixel.y = first_pixel.y;
	pixel.z = first_pixel.z;

	Color globalcolor;
	Ray ray;
	Point nearest_point;

	for (int i = 0; i < no_of_scanlines; i++)
	{
		for (int j = 0; j < no_of_pixels; j++)
		{
			RayInit(pixel, eye, &ray);
			globalcolor = TraceRay(sphere, ray, 0, &nearest_point);

			glColor3f(globalcolor.r, globalcolor.g, globalcolor.b);
			glBegin(GL_POINTS);
			glVertex3f(nearest_point.x, nearest_point.y, nearest_point.z);
			glEnd();

			pixel.x = pixel.x + delta_X;
		}
		pixel.x = first_pixel.x;
		pixel.z = first_pixel.z;

		pixel.y = first_pixel.y - delta_Y;
		first_pixel.y = pixel.y;

	}
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int a;
	if (w>h) a = h;
	else a = w;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0,     // eye's position
		0.0, 0.0, 1.0,     // center of interest
		0.0f, 1.0f, 0.0f);   // up direction
}

void KeyListener(unsigned char Key, int x, int y)
{
	SizeChange.ChangeValue(Key, x, y);
}