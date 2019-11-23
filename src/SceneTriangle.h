#ifndef SCENE_TRIANGLE_H
#define SCENE_TRIANGLE_H

#include "Material.h"
#include "Triangle.h"

struct SceneTriangle : public Triangle
{
	Material* material;
};

#endif // SCENE_TRIANGLE_H