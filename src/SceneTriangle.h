#ifndef SCENE_TRIANGLE_H
#define SCENE_TRIANGLE_H

#include "Material.h"
#include "Triangle.h"

class SceneTriangle : public Triangle
{
public:
	const Material& getMaterial() const { return *material; }

private:
	Material* material;
};

#endif // SCENE_TRIANGLE_H