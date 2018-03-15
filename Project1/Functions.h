#include "Geometry.h"

Point eye;
Light light;
Screen screen;

const int Sphere_no = 4;
float sizeMult = 1.0;
Sphere sphere[Sphere_no];

bool intersection(Ray r, Sphere s, Point *p, float *t)
{
	float discriminant;
	float t1, t2;

	Vector d;
	sub(r.p2, r.p1, &d);

	Vector e_c;
	sub(r.p1, s.centre, &e_c);

	float B;
	B = dot_product(d, e_c);

	float B2;
	B2 = B * B;

	float A;
	A = dot_product(d, d);

	float C;
	C = dot_product(e_c, e_c) - s.radius * s.radius;

	discriminant = B2 - A * C;

	if (discriminant < 0)
	{
		return false;
	}
	else if (discriminant == 0.0)
	{
		t1 = -B / A;
		Vector td;
		scalar_mult(t1, d, &td);
		sum(r.p1, td, p);

		*t = t1;
		if (t1 > 0.0) return true;
		else return false;

	}
	else
	{
		t1 = (-B + sqrt(discriminant)) / A;
		t2 = (-B - sqrt(discriminant)) / A;

		if (t1 > t2) *t = t2;
		else *t = t1;

		Vector td;
		scalar_mult(*t, d, &td);
		sum(r.p1, td, p);

		if ((t1 > 0.0) && (t2 > 0.0)) return true;
		else return false;
	}
}

void Setup()
{
	screen.height = 2.0;
	screen.width = 3.0;

	screen.x = 1920;
	screen.y = 1080;

	screen.z = 1.5;

	//Light source set to white colour
	light.intensity_r = 1.0;
	light.intensity_g = 1.0;
	light.intensity_b = 1.0;

	light.position.x = 0.0;
	light.position.y = 2.0;
	light.position.z = 20.0;

	eye.x = 0.0;
	eye.y = 0.0;
	eye.z = 5.0;
	/*
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			sphere[i].centre.x = 0.0;
			sphere[i].centre.y = 0.0;
			sphere[i].centre.z = 0.0;
		}
		else
		{
			sphere[i].centre.x = sphere[i - 1].centre.x + 1;
			sphere[i].centre.y = 0.0;
			sphere[i].centre.z = 0.0;
		}

		sphere[i].radius = 0.5;

		//Sphere material set up
		sphere[i].ambient_r = 0.3;
		sphere[i].ambient_g = 0.3;
		sphere[i].ambient_b = 0.3;

		sphere[i].diffuse_r = 0.0;
		sphere[i].diffuse_g = 0.0;
		sphere[i].diffuse_b = 0.9;

		sphere[i].specular_r = 0.9;
		sphere[i].specular_g = 0.9;
		sphere[i].specular_b = 0.9;
	}*/
	
	// shpere
	sphere[0].centre.x = -0.75;
	sphere[0].centre.y = -0.75;
	sphere[0].centre.z = 0.0;

	sphere[0].radius = 0.5 * sizeMult;

	// ka
	sphere[0].ambient_b = 0.3;
	sphere[0].ambient_g = 0.3;
	sphere[0].ambient_r = 0.3;

	// diffuse_
	sphere[0].diffuse_b = 0.0;
	sphere[0].diffuse_g = 0.0;
	sphere[0].diffuse_r = 0.9;

	// specular_
	sphere[0].specular_g = 0.9;
	sphere[0].specular_r = 0.9;
	sphere[0].specular_b = 0.9;

	// sphere2
	sphere[1].centre.x = 0.75;
	sphere[1].centre.y = -0.5;
	sphere[1].centre.z = 0.0;

	sphere[1].radius = 0.75 * sizeMult;

	// ambient_
	sphere[1].ambient_b = 0.3;
	sphere[1].ambient_g = 0.3;
	sphere[1].ambient_r = 0.3;

	// diffuse_
	sphere[1].diffuse_b = 0.9;
	sphere[1].diffuse_g = 0.0;
	sphere[1].diffuse_r = 0.0;

	// specular_
	sphere[1].specular_g = 0.9;
	sphere[1].specular_r = 0.9;
	sphere[1].specular_b = 0.9;

	// shpere3
	sphere[2].centre.x = -0.75;
	sphere[2].centre.y = 0.75;
	sphere[2].centre.z = 0.0;

	sphere[2].radius = 0.25 * sizeMult;

	// ambient_
	sphere[2].ambient_b = 0.3;
	sphere[2].ambient_g = 0.3;
	sphere[2].ambient_r = 0.3;

	// diffuse_
	sphere[2].diffuse_b = 0.0;
	sphere[2].diffuse_g = 0.9;
	sphere[2].diffuse_r = 0.0;

	// specular_
	sphere[2].specular_g = 0.9;
	sphere[2].specular_r = 0.9;
	sphere[2].specular_b = 0.9;

	sphere[3].centre.x = 0.75;
	sphere[3].centre.y = 0.75;
	sphere[3].centre.z = 0.0;

	sphere[3].radius = 0.3 * sizeMult;

	// ambient_
	sphere[3].ambient_b = 0.3;
	sphere[3].ambient_g = 0.3;
	sphere[3].ambient_r = 0.3;

	// diffuse_
	sphere[3].diffuse_b = 0.0;
	sphere[3].diffuse_g = 0.3;
	sphere[3].diffuse_r = 0.7;

	// specular_
	sphere[3].specular_g = 0.9;
	sphere[3].specular_r = 0.9;
	sphere[3].specular_b = 0.9;
}

void RayInit(Point pixel, Point eye, Ray *ray)
{
	(*ray).p1.x = eye.x;
	(*ray).p1.y = eye.y;
	(*ray).p1.z = eye.z;


	(*ray).p2.x = pixel.x;
	(*ray).p2.y = pixel.y;
	(*ray).p2.z = pixel.z;
}

void RayRender(Point p, Light light, Point eye, Sphere sphere, Color* color)
{
	Vector normal;
	normal.x = p.x - sphere.centre.x;
	normal.y = p.y - sphere.centre.y;
	normal.z = p.z - sphere.centre.z;
	unit1(normal, &normal);

	Vector L;
	L.x = light.position.x - p.x;
	L.y = light.position.y - p.y;
	L.z = light.position.z - p.z;
	unit1(L, &L);

	Vector V;
	V.x = eye.x - p.x;
	V.y = eye.y - p.y;
	V.z = eye.z - p.z;
	unit1(V, &V);

	Vector H;
	Vector tmp_H;

	sum(L, V, &tmp_H);
	scalar_mult(0.5, tmp_H, &H);

	float LdotN;
	LdotN = dot_product(L, normal);

	float HdotN;
	HdotN = dot_product(H, normal);

	float Ambient_r = 0.3, Ambient_g = 0.3, Ambient_b = 0.3;

	float HdotN_n = pow(HdotN, 250);

	if (LdotN >= 0.0)
	{
		(*color).r = sphere.ambient_r * Ambient_r + sphere.diffuse_r*light.intensity_r*LdotN + sphere.specular_r * HdotN_n;
		(*color).g = sphere.ambient_g * Ambient_g + sphere.diffuse_g*light.intensity_g*LdotN + sphere.specular_g * HdotN_n;
		(*color).b = sphere.ambient_b * Ambient_b + sphere.diffuse_b*light.intensity_b*LdotN + sphere.specular_b * HdotN_n;

		if ((*color).r > 1.0) (*color).r = 1.0;
		if ((*color).g > 1.0) (*color).g = 1.0;
		if ((*color).b > 1.0) (*color).b = 1.0;
	}
	else
	{
		(*color).r = sphere.ambient_r * Ambient_r;
		(*color).g = sphere.ambient_g * Ambient_g;
		(*color).b = sphere.ambient_b * Ambient_b;
	}

	if ((*color).r < 0.0) (*color).r = 0.0;
	if ((*color).g < 0.0) (*color).g = 0.0;
	if ((*color).b < 0.0) (*color).b = 0.0;
}

void ReflectRay(Point p, Sphere sphere, Ray* reflected)
{
	Vector normal;
	normal.x = p.x - sphere.centre.x;
	normal.y = p.y - sphere.centre.y;
	normal.z = p.z - sphere.centre.z;
	unit1(normal, &normal);

	Vector r;
	r.x = eye.x - p.x;
	r.y = eye.y - p.y;
	r.z = eye.z - p.z;
	unit1(r, &r);

	float r_dot_n;
	r_dot_n = dot_product(r, normal);

	Vector knormal;
	scalar_mult(2.0 * r_dot_n, normal, &knormal);

	Vector F;
	sub(knormal, r, &F);

	F.x = F.x + p.x;
	F.y = F.y + p.y;
	F.z = F.z + p.z;

	Point p1;
	p1.x = F.x;
	p1.y = F.y;
	p1.z = F.z;

	RayInit(p1, p, reflected);

}

Color TraceRay(Sphere* sphere, Ray r, int depth, Point* p)
{
	Color local_color, reflected_color, global_color, background;
	Point tmp;

	float nearest_t;
	float t;

	int sphere_index;
	bool is_intersected = false;

	const int max_depth = 5;
	const float big_num = 1000.0;

	nearest_t = big_num;

	global_color.r = global_color.g = global_color.b = 0.0;
	local_color.r = local_color.g = local_color.b = 0.0;
	reflected_color.r = reflected_color.g = reflected_color.b = 0.0;
	background.r = background.g = background.b = 0.0;

	if (depth > max_depth)
	{
		return background;
	}
	else
	{
		for (int k = 0; k < Sphere_no; k++)
		{
			if (intersection(r, sphere[k], &tmp, &t))
			{
				is_intersected = true;
				if (t < nearest_t)
				{
					nearest_t = t;
					(*p).x = tmp.x;
					(*p).y = tmp.y;
					(*p).z = tmp.z;
					sphere_index = k;
				}
			}
		}
		if (is_intersected == true)
		{
			RayRender(*p, light, eye, sphere[sphere_index], &local_color);

			nearest_t = big_num;
			is_intersected = false;

			Ray reflected;
			ReflectRay(*p, sphere[sphere_index], &reflected);

			reflected_color = TraceRay(sphere, reflected, depth + 1, &tmp);
			global_color.r = local_color.r + reflected_color.r * 0.5;
			global_color.g = local_color.g + reflected_color.g * 0.5;
			global_color.b = local_color.b + reflected_color.b * 0.5;

			return global_color;
		}
		else return background;
	}
}

class SphereChanger {
public:
	void ChangeValue(unsigned char Key, int x, int y)
	{
		switch (Key)
		{
		case 'w':
			if (sizeMult <= 1.5)
				sizeMult += 0.1;
			else
				sizeMult = 0.5;
			break;
		case 's':
			if (sizeMult >= 0.5)
				sizeMult -= 0.1;
			else
				sizeMult = 1.5;
			break;
		default:
			break;
		}
		std::cout << "Size multiplier: " << sizeMult << std::endl;
	}
};