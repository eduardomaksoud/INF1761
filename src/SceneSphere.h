#ifndef SCENE_SPHERE_H
#define SCENE_SPHERE_H

#include "Material.h"
#include "Sphere.h"

struct SceneSphere : public Sphere
{
	Material* material;
};

#endif // SCENE_SPHERE_H