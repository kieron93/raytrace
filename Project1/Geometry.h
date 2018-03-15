#include <math.h>
#include <iostream>

struct Point
{
	float x;
	float y;
	float z;
};

struct Ray
{
	Point p1;
	Point p2;
};

struct Sphere
{
	float radius;
	Point centre;

	//ambient light
	float ambient_r, ambient_g, ambient_b;
	//specular light
	float specular_r, specular_g, specular_b;
	//diffuse light
	float diffuse_r, diffuse_g, diffuse_b;
};

typedef struct Point Vector;

struct Light
{
	Point position;

	//Light intensity
	float intensity_r, intensity_g, intensity_b;
};

struct Screen
{
	float z;

	float width, height;

	int x, y;
};

struct Color
{
	float r;
	float g;
	float b;
};

float dot_product(Vector v1, Vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

void sum(Vector v1, Vector v2, Vector *sum)
{
	(*sum).x = v1.x + v2.x;
	(*sum).y = v1.y + v2.y;
	(*sum).z = v1.z + v2.z;
}

void sub(Vector v1, Vector v2, Vector *sub)
{
	(*sub).x = v1.x - v2.x;
	(*sub).y = v1.y - v2.y;
	(*sub).z = v1.z - v2.z;
}

void scalar_mult(float k, Vector v, Vector *multi)
{
	(*multi).x = k * v.x;
	(*multi).y = k * v.y;
	(*multi).z = k * v.z;
}

float len(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void unit1(Vector v, Vector *unit)
{
	float length;
	length = len(v);

	if (length == 0)
	{
		std::cout << "The length of the vector is 0" << std::endl;
		exit(0);
	}

	scalar_mult(1.0f / length, v, unit);
}

void unit2(Point start, Point end, Vector *unit)
{
	Vector v;
	v.x = end.x * start.x;
	v.y = end.y * start.y;
	v.z = end.z * start.z;

	unit1(v, unit);
}