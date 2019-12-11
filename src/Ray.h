#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
#include "Triangle.h"
#include "Sphere.h"

struct Ray
{
	Vector3 origin;
	Vector3 direction;

	bool interceptsWith(const Triangle& t, Vector3* interception) const;
	bool interceptsWith(const Triangle& t, Vector3* interception, Vector3* normal) const;
	bool interceptsWith(const Sphere& s, float* firstInterception, float* secondInterception) const;
	float getReflectionAngle(const Sphere& s, const Vector3& p);

};

#endif // RAY_H