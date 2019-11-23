#include "Scene.h"

#include "Ray.h"

#include <utility>
#include <algorithm>
#include <future>
#include <vector>
/*
void Scene::render(RenderingFrame& renderingFrame) const
{
	static std::vector<std::future<void>> futures;
	int constexpr CORE_NUMBERS = 8;

	int widthStep = renderingFrame.getWidth() / CORE_NUMBERS;
	int width = widthStep;
	int height = renderingFrame.getHeight();
	int firstX = 0;
	int firstY = 0;

	for (int i = 0; i < CORE_NUMBERS; ++i)
	{
		futures.push_back(std::async(std::launch::async, std::bind(&Scene::internalRender, this, renderingFrame, width, height, firstX, firstY)));

		firstX = width;
		width += widthStep;
	}

	for (auto& f : futures)
	{
		f.wait();
	}
	futures.clear();
}*/

void Scene::render(RenderingFrame& renderingFrame) const
{
	int constexpr CORE_NUMBERS = 8;

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

void Scene::internalRender(RenderingFrame& renderingFrame, int width, int height, int firstX, int firstY) const
{
	Ray r;

	Vector3 interception;

	float distance;
	float horizontalRotation;
	float verticalRotation;

	bool intercepted;
	float nearestTDistance;
	const SceneTriangle* nearestT;

	r.origin = mainCamera.getPosition();

	for (int i = firstX; i < width; ++i)
	{
		horizontalRotation = (i / (float)(renderingFrame.getWidth() - 1)) * mainCamera.getHorizontalFOV() - mainCamera.getHorizontalFOV()/2;		
		
		for (int j = firstY; j < height; ++j)
		{
			nearestT = nullptr;
			nearestTDistance = INFINITY;
			intercepted = false;

			verticalRotation = (j / (float)(renderingFrame.getHeight() - 1)) * mainCamera.getVerticalFOV() - mainCamera.getVerticalFOV()/2;
			r.direction = mainCamera.getLocalZAxis();
			r.direction.rotate(mainCamera.getLocalXAxis(), verticalRotation);
			r.direction.rotate(mainCamera.getLocalYAxis(), horizontalRotation);
			
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
				
				color.r *= mult * color.r;
				color.g *= mult * color.g;
				color.b *= mult * color.b;

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