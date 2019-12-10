#include "Ray.h"
#include <stdio.h>
#include <utility>

bool Ray::interceptsWith(const Triangle& t, Vector3* interception, Vector3* normal) const
{
	Vector3 ab = t.vertexB - t.vertexA;
	Vector3 bc = t.vertexC - t.vertexB;

	*normal = ab.cross(bc);

	if (normal->dot(direction) == 0)
	{
		return false;
	}

	normal->normalize();

	float k = (normal->dot(t.vertexA) - normal->dot(origin)) / normal->dot(direction);

	// If k is less than zero, it means that the plane we are evaluating is standing behind the origin of our ray.
	if (k < 0)
	{
		return false;
	}

	interception->x = direction.x * k + origin.x;
	interception->y = direction.y * k + origin.y;
	interception->z = direction.z * k + origin.z;

	if (normal->dot(ab.cross(*interception - t.vertexA)) < 0)
		return false;

	if (normal->dot(bc.cross(*interception - t.vertexB)) < 0)
		return false;

	if (normal->dot((t.vertexA - t.vertexC).cross(*interception - t.vertexC)) < 0)
		return false;

	return true; // this ray hits the GeometryType::Triangle
}

bool Ray::interceptsWith(const Triangle& t, Vector3* interception) const
{
	Vector3 normal;
	return interceptsWith(t, interception, &normal);
}

bool Ray::interceptsWith(const Sphere& s, double *firstInterception,double *secondInterception) const
{
	Vector3 originToCenter = s.center - origin;
	float t = originToCenter.dot(direction);
	 
	if (t < 0)
	{ 
		return false;
	}

	float y = originToCenter.dot(originToCenter) - t * t;
	if (y > s.radius) return false;

	float x = sqrt(s.radius - y);
	*firstInterception = t - x;
	*secondInterception =  t + x;

	if (*firstInterception > * secondInterception)
	{
		std::swap(*firstInterception, *secondInterception);
	}
	
	if (*firstInterception < 0)
	{
		*firstInterception = *secondInterception;
		if (*firstInterception < 0) return false;
	}

	return true; // this ray hits the sphere
}

float Ray::getReflectionAngle(const Sphere& s, const Vector3& p)
{
	Vector3 normal = (s.center - p) / s.radius;
	float reflection = this->direction.dot(normal);

	return reflection;
}



