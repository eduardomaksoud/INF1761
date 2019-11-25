#include "Scene.h"

#include "Ray.h"

#include <utility>
#include <algorithm>
#include <future>
#include <vector>

void Scene::render(RenderingFrame& renderingFrame) const
{
	int constexpr CORE_NUMBERS = 1;

	int widthStep = renderingFrame.getWidth() / CORE_NUMBERS;
	int width = widthStep;
	int height = renderingFrame.getHeight();
	int firstX = 0;
	int firstY = 0;

	for (int i = 0; i < CORE_NUMBERS; ++i)
	{
		auto f = std::async(std::launch::async, std::bind(&Scene::internalRender, this, renderingFrame, width, height, firstX, firstY));

		firstX = width;
		width += widthStep;
	}
}

void Scene::internalRender(RenderingFrame& renderingFrame, int lastX, int lastY, int firstX, int firstY) const
{
	Ray r;

	Vector3 interception;

	float distance;
	float horizontalRatio;
	float verticalRatio;
	float horizontalRotation;
	float verticalRotation;

	bool intercepted;
	float nearestTDistance;
	const SceneTriangle* nearestT;


	r.origin = mainCamera.getPosition();

	for (int i = firstX; i < lastX; ++i)
	{
		horizontalRatio = (i / (float)(renderingFrame.getWidth() - 1));	
		
		for (int j = firstY; j < lastY; ++j)
		{
			nearestT = nullptr;
			nearestTDistance = INFINITY;
			intercepted = false;

			verticalRatio = (j / (float)(renderingFrame.getHeight() - 1));

			r.direction = mainCamera.getLocalZAxis() + mainCamera.getLocalXAxis() * (horizontalRatio - 0.5) + mainCamera.getLocalYAxis() * (verticalRatio - 0.5);
			r.direction.normalize();
			
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
				auto color = nearestT->material->getColor();

				float mult = std::max(0.0F, (1 - nearestTDistance / mainCamera.getViewDistance()));
				
				color.r = mult * color.r;
				color.g = mult * color.g;
				color.b = mult * color.b;

				renderingFrame.setColor(color);
			}
			else
			{
				renderingFrame.setColor(0, 0, 0);
			}
			renderingFrame.drawPoint(i, renderingFrame.getHeight() - j);
		}
	}
}