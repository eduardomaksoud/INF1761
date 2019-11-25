#include "Ray.h"
#include <stdio.h>

//
//	To cope for floating point imprecisions, use this function to check if two floats
//	are equal not. You can adjust the 'ERROR_MARGIN' constant as desired.
//
static bool BiasedEquals(float a, float b)
{
	constexpr float ERROR_MARGIN = 0.05;
	if constexpr (ERROR_MARGIN != 0)
	{
		return (a <= (b + ERROR_MARGIN)) && (a >= (b - ERROR_MARGIN));
	}
	else
	{
		return a == b;
	}
}

bool Ray::interceptsWith(const Triangle& t, Vector3* interception)
{
	Vector3 ab = t.vertexB - t.vertexA;
	Vector3 bc = t.vertexC - t.vertexB;
	
	Vector3 normal = ab.cross(bc);

	if (normal.dot(direction) == 0)
	{
		return false;
	}

	normal.normalize();
	
	float k = (normal.dot(t.vertexA) - normal.dot(origin)) / normal.dot(direction);
	
	// If k is less than zero, it means that the plane we are evaluating is standing behind the origin of our ray.
	if (k < 0)
	{
		return false;
	}

	interception->x = direction.x * k + origin.x;
	interception->y = direction.y * k + origin.y;
	interception->z = direction.z * k + origin.z;

	if (normal.dot(ab.cross(*interception - t.vertexA)) < 0)
		return false;

	if (normal.dot(bc.cross(*interception - t.vertexB)) < 0)
		return false;

	if (normal.dot((t.vertexA - t.vertexC).cross(*interception - t.vertexC)) < 0)
		return false;

	return true; // this ray hits the triangle
}


