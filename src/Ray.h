#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
#include "Triangle.h"
#include "Sphere.h"

struct Ray
{
	Vector3 origin;
	Vector3 direction;

	bool interceptsWith(const Triangle& t, Vector3* interception);
	//bool interceptsWith(const Sphere& s, Vector3* interception);
};

#endif // RAY_H