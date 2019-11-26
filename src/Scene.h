#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Camera.h"
#include "SceneTriangle.h"
#include "SceneSphere.h"
#include "RenderingFrame.h"

class Scene
{
public:
	void render(RenderingFrame& r) const;

	Camera& getMainCamera() { return mainCamera; }
	const Camera& getMainCamera() const { return mainCamera; }

	SceneTriangle& getTriangle(int idx)
	{
		return triangles[idx];
	}

	const SceneTriangle& getTriangle(int idx) const
	{
		return triangles[idx];
	}

	int addTriangle(const SceneTriangle& t)
	{
		triangles.push_back(t);
		return triangles.size() - 1;
	}

	SceneSphere& getSphere(int idx) 
	{
		return spheres[idx];
	}

	const SceneSphere& getSphere(int idx) const
	{
		return spheres[idx];
	}

	int addSphere(const SceneSphere& s)
	{
		spheres.push_back(s);
		return spheres.size() - 1;
	}

private:
	std::vector<SceneTriangle> triangles;
	std::vector<SceneSphere> spheres;
	Camera mainCamera;

	void internalRender(RenderingFrame& f, int w, int h, int firstX, int firstY) const;
};

#endif // SCENE_H