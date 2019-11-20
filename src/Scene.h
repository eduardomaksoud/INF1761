#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Camera.h"
#include "SceneTriangle.h"
#include "RenderingFrame.h"

class Scene
{
public:
	void Render(RenderingFrame& r) const;

	Camera& getMainCamera() { return mainCamera; }
	const Camera& getMainCamera() const { return mainCamera; }

private:
	std::vector<SceneTriangle> triangles;
	Camera mainCamera;
};

#endif // SCENE_H