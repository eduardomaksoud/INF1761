#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Camera.h"
#include "SceneTriangle.h"
#include "RenderingFrame.h"

class Scene
{
public:
	void render(RenderingFrame& r) const;

	Camera& getMainCamera() { return mainCamera; }
	const Camera& getMainCamera() const { return mainCamera; }

	void AddTriangle(const SceneTriangle& t)
	{
		triangles.push_back(t);
	}

private:
	std::vector<SceneTriangle> triangles;
	Camera mainCamera;

	void internalRender(RenderingFrame& f, int w, int h, int firstX, int firstY) const;
};

#endif // SCENE_H