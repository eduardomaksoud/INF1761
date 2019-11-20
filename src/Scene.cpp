#include "Scene.h"

#include "Ray.h"

void Scene::Render(RenderingFrame& renderingFrame) const
{
	int a;
	Ray r;

	Vector3 interception;

	float distance;
	bool intercepted;
	float nearestTDistance = INFINITY;
	const SceneTriangle* nearestT = nullptr;

	for (int i = 0; i < renderingFrame.getWidth(); ++i)
	{
		for (int j = 0; j < renderingFrame.getHeight(); ++j)
		{
			r.origin = mainCamera.getPosition();
			//r.direction = IMPLEMENTAR

			for (const SceneTriangle& t : triangles)
			{
				intercepted = r.interceptsWith(t, &interception);
				distance = (interception - r.origin).norm();

				if (intercepted && distance < nearestTDistance)
				{
					nearestTDistance = distance;
					nearestT = &t;
				}
			}

			if (nearestT != nullptr)
			{
				renderingFrame.setColor(nearestT->getMaterial().getColor());
				renderingFrame.drawPoint(i, j);
			}
		}
	}
}