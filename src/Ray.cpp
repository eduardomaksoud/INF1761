#include "Ray.h"

bool Ray::interceptsWith(const Triangle& t, Vector3* interception)
{
	Vector3 ab = t.vertexA - t.vertexB;
	Vector3 bc = t.vertexB - t.vertexC;
	
	Vector3 normal = ab.cross(bc);
	
	float d = -(normal.x * t.vertexA.x + normal.y * t.vertexA.y + normal.z + t.vertexA.z);

	float k = (-d + normal.x * origin.x + normal.y * origin.y + normal.z * origin.z) / (-normal.x * direction.x - normal.y * direction.y - normal.z * direction.z);

	// If k is less than zero, it means that the plane we are evaluating is standing behind the origin of our ray.
	if (k < 0)
	{
		return false;
	}

	interception->x = direction.x * k + origin.x;
	interception->y = direction.y * k + origin.y;
	interception->z = direction.z * k + origin.z;

	float triangleAreaDouble = normal.norm();
	float comparisonAreaDouble = (*interception - t.vertexA).cross(*interception - t.vertexC).norm()
		+ (*interception - t.vertexA).cross(*interception - t.vertexB).norm()
		+ (*interception - t.vertexB).cross(*interception - t.vertexC).norm();

	return triangleAreaDouble == comparisonAreaDouble;
}
