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
/*
bool Ray::interceptsWith(const Triangle& t, Vector3* interception)
{
	Vector3 ab = t.vertexB - t.vertexA;
	Vector3 bc = t.vertexC - t.vertexB;

	Vector3 normal = ab.cross(bc);

	float d = normal.x * t.vertexA.x + normal.y * t.vertexA.y + normal.z * t.vertexA.z;

	interception->x = (d - normal.y * (origin.y - direction.y * origin.x / direction.x) - normal.z * (origin.z - direction.z * origin.x / direction.x))
		/ (normal.x + normal.y * (direction.y / direction.x) + normal.z * (direction.z / direction.x));

	float k = (interception->x - origin.x);

	// If k is less than zero, it means that the plane we are evaluating is standing behind the origin of our ray.
	if (k < 0)
	{
		return false;
	}

	interception->y = (direction.y / direction.x) * k + origin.y;
	interception->z = (direction.z / direction.x) * k + origin.z;

	float triangleAreaDouble = normal.norm();
	float comparisonAreaDouble = (*interception - t.vertexA).cross(*interception - t.vertexC).norm()
		+ (*interception - t.vertexA).cross(*interception - t.vertexB).norm()
		+ (*interception - t.vertexB).cross(*interception - t.vertexC).norm();
	
	return BiasedEquals(triangleAreaDouble, comparisonAreaDouble);
}*/

bool Ray::interceptsWith(const Triangle& t, Vector3* interception)
{
	Vector3 ab = t.vertexB - t.vertexA;
	Vector3 bc = t.vertexC - t.vertexB;
	
	Vector3 normal = ab.cross(bc);

	if (normal.dot(direction) == 0)
	{
		return false;
	}

	float triangleAreaDouble = normal.norm();
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

	float comparisonAreaDouble = (*interception - t.vertexA).cross(*interception - t.vertexC).norm()
		+ (*interception - t.vertexA).cross(*interception - t.vertexB).norm()
		+ (*interception - t.vertexB).cross(*interception - t.vertexC).norm();
	
	//return triangleAreaDouble == comparisonAreaDouble;
	return BiasedEquals(triangleAreaDouble, comparisonAreaDouble);
}

