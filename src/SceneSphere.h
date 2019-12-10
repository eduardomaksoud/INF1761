#ifndef SCENE_SPHERE_H
#define SCENE_SPHERE_H

#include "Material.h"
#include "Sphere.h"

enum class SphereSide
{
	Negative,
	Positive
};

struct SceneSphere : public Sphere
{
	Material* material;
};

#endif // SCENE_SPHERE_H