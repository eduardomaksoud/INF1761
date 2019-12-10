#include "Scene.h"

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
	SDL_Color color;
	float horizontalRotation;
	float verticalRotation;
	float horizontalRatio;
	float verticalRatio;

	r.origin = mainCamera.getPosition();

	for (int i = firstX; i < lastX; ++i)
	{
		horizontalRatio = (i / (float)(renderingFrame.getWidth() - 1));

		for (int j = firstY; j < lastY; ++j)
		{
			verticalRatio = (j / (float)(renderingFrame.getHeight() - 1));

			r.direction = mainCamera.getLocalZAxis() + mainCamera.getLocalXAxis() * (horizontalRatio - 0.5) 
			+ mainCamera.getLocalYAxis() * (verticalRatio - 0.5);
			r.direction.normalize();

			color = traceRay(r);
			renderingFrame.setColor(color);
			renderingFrame.drawPoint(i, renderingFrame.getHeight() - j);
		}
	}
}

void Scene::findInterceptionWithSceneObjects(const Ray& r, Scene::RayInterceptionData& ret) const
{
	bool intercepted;
	Vector3 tempInterception;
	float nearestDistance = INFINITY;
	float tempDistance = INFINITY;
	ret.material = nullptr;

	for (const SceneTriangle& t : triangles)
	{
		ret.geometryType = GeometryType::Triangle;
		intercepted = r.interceptsWith(t, &tempInterception, &ret.normal);
		tempDistance = (tempInterception - r.origin).norm();

		if (intercepted && tempDistance < ret.distance)
		{
			ret.interception = tempInterception;
			ret.distance = tempDistance;
			ret.material = t.material;
		}
	}
	for (const SceneSphere& s : spheres)
	{
		ret.geometryType = GeometryType::Sphere;
		ret.sphereSide = SphereSide::Positive;
		double sphereFirstInterception = INFINITY;
		double sphereSecondInterception = INFINITY;

		intercepted = r.interceptsWith(s, &sphereFirstInterception, &sphereSecondInterception);

		if (intercepted)
		{
			if (sphereFirstInterception < 0)
			{
				ret.sphereSide = SphereSide::Negative;
				sphereFirstInterception = sphereSecondInterception;
			}
			if (sphereFirstInterception < nearestDistance)
			{
				nearestDistance = sphereFirstInterception;
				ret.material = s.material;

				ret.interception = r.origin + r.direction * sphereFirstInterception;
				ret.normal = (s.center - ret.interception) / s.radius;
				ret.normal.normalize();
			}	
		}
	}
}

SDL_Color Scene::traceRay(const Ray& r) const
{
	RayInterceptionData rayData;
	RayInterceptionData shadowRayData;

	findInterceptionWithSceneObjects(r, rayData);

	// After the call for "findInterceptionWithSceneObjects", rayData contains all data needed
	// to analyze whether the specified ray intercepted a scene object (rayData.material != nullptr)
	// and information about such interception.

	if (rayData.material != nullptr)
	{
		float vis = 1;
		float cosTheta;
		float bias = 0.95f;

		SDL_Color finalColor;
		SDL_Color materialColor;
		float white[2];
		SDL_Color combinedColor;

		Ray shadowRay;
		Vector3 shadowDirection;

		Vector3 shadowRayInterception;
		float shadowRayFirstInterception;
		float shadowRaySecondInterception;

		finalColor.r = 0;
		finalColor.g = 0;
		finalColor.b = 0;

		for (const PointLight& l : lightSources)
		{
			if (rayData.geometryType == GeometryType::Sphere)
			{/*
				if (rayData.sphereSide == SphereSide::Negative)
				{
					shadowDirection = rayData.interception -l.position;
				}
				else
				{
					shadowDirection = l.position - rayData.interception;
				}*/
				shadowDirection = rayData.interception - l.position;
				shadowDirection.normalize();
				shadowRay.direction = -1*shadowDirection;
				shadowRay.origin = (rayData.interception + rayData.normal * bias);

				findInterceptionWithSceneObjects(shadowRay, shadowRayData);

				bool intercepted = shadowRayData.material != nullptr;

				if (!intercepted)
				{
					materialColor = rayData.material->getDiffuseColor();

					cosTheta = std::max(0.f, rayData.normal.dot(shadowDirection));

					white[0] = std::min(materialColor.r, std::min(materialColor.g, materialColor.b));
					white[1] = std::min(l.color.r, std::min(l.color.g, l.color.b));

					combinedColor.r = (materialColor.r + l.color.r - white[0] - white[1]) / 2;
					combinedColor.g = (materialColor.g + l.color.g - white[0] - white[1]) / 2;
					combinedColor.b = (materialColor.b + l.color.b - white[0] - white[1]) / 2;

					finalColor.r += vis * combinedColor.r * l.intensity * cosTheta;
					finalColor.g += vis * combinedColor.g * l.intensity * cosTheta;
					finalColor.b += vis * combinedColor.b * l.intensity * cosTheta;
				}
			}
			else
			{
				shadowDirection = rayData.interception - l.position;
				shadowDirection.normalize();
				shadowRay.direction = shadowDirection;
				shadowRay.origin = rayData.interception;

				findInterceptionWithSceneObjects(shadowRay, shadowRayData);

				bool intercepted = shadowRayData.material != nullptr;
				if (!intercepted)
				{
					materialColor = rayData.material->getDiffuseColor();

					white[0] = std::min(materialColor.r, std::min(materialColor.g, materialColor.b));
					white[1] = std::min(l.color.r, std::min(l.color.g, l.color.b));

					combinedColor.r = (materialColor.r + l.color.r - white[0] - white[1]) / 2;
					combinedColor.g = (materialColor.g + l.color.g - white[0] - white[1]) / 2;
					combinedColor.b = (materialColor.b + l.color.b - white[0] - white[1]) / 2;

					finalColor.r += vis * combinedColor.r * l.intensity;
					finalColor.g += vis * combinedColor.g * l.intensity;
					finalColor.b += vis * combinedColor.b * l.intensity;
				}
			}
		}
		return finalColor;
	}
	else
	{
		return SDL_Color{ 0,0,0,1 };
	}
}

/*
SDL_Color Scene::traceRay(const Ray& r) const
{
	Vector3 interception;
	Vector3 finalInterception;
	Vector3 normal;

	SphereSide sphereSide = SphereSide::Positive;
	GeometryType geometryRendered;

	SceneTriangle blockTriangle;
	SceneSphere blockSphere;
	SceneSphere sphereCollider;

	float sphereFirstInterception;
	float sphereSecondInterception;
	float temp;

	float distance;

	bool intercepted;
	float nearestDistance;

	const Material* nearestMaterial;

	nearestMaterial = nullptr;
	nearestDistance = INFINITY;
		sphereFirstInterception = INFINITY;
		sphereSecondInterception = INFINITY;

	intercepted = false;

	for (const SceneTriangle& t : triangles)
	{
		geometryRendered = GeometryType::Triangle;
		intercepted = r.interceptsWith(t, &interception, &normal);
		distance = (interception - r.origin).norm();

		if (intercepted && distance < nearestDistance)
		{
			finalInterception = interception;
			nearestDistance = distance;
			nearestMaterial = t.material;
		}
	}
	for (const SceneSphere& s : spheres)
	{
		geometryRendered = GeometryType::Sphere;


		intercepted = r.interceptsWith(s, &sphereFirstInterception, &sphereSecondInterception);

		if (intercepted)
		{
			if (sphereFirstInterception < 0)
			{
				sphereSide = SphereSide::Negative;
				temp = sphereFirstInterception;
				sphereFirstInterception = sphereSecondInterception;
				sphereSecondInterception = temp;
			}
			if (sphereFirstInterception < nearestDistance)
			{
				nearestDistance = sphereFirstInterception;
				nearestMaterial = s.material;

				finalInterception = r.origin + r.direction * sphereFirstInterception;
				normal = (s.center - finalInterception) / s.radius;
				normal.normalize();
			}
		}
	}

	if (nearestMaterial != nullptr)
	{
		float vis = 1;
		float cosTheta;

		SDL_Color finalColor;
		SDL_Color materialColor;
		float white[2];
		SDL_Color combinedColor;

		Ray shadowRay;
		Vector3 shadowDirection;

		Vector3 shadowRayInterception;
		float shadowRayFirstInterception;
		float shadowRaySecondInterception;

		finalColor.r = 0;
		finalColor.g = 0;
		finalColor.b = 0;

		for (const PointLight& l : lightSources)
		{
			shadowDirection = finalInterception - l.position;
			if (geometryRendered == GeometryType::Sphere)
			{
				if (sphereSide == SphereSide::Negative)
				{
					shadowDirection = finalInterception - l.position;
				}
				else
				{
					shadowDirection = l.position - finalInterception;
				}

				shadowDirection.normalize();
				shadowRay.direction = shadowDirection;
				shadowRay.origin = finalInterception;

				intercepted = shadowRay.interceptsWith(blockSphere, &shadowRayFirstInterception, &shadowRaySecondInterception);

				if (!intercepted)
				{
					/* Is visible

					materialColor = nearestMaterial->getDiffuseColor();

					cosTheta = std::max(0.f, normal.dot(shadowDirection));

					white[0] = std::min(materialColor.r, std::min(materialColor.g, materialColor.b));
					white[1] = std::min(l.color.r, std::min(l.color.g, l.color.b));

					combinedColor.r = (materialColor.r + l.color.r - white[0] - white[1]) / 2;
					combinedColor.g = (materialColor.g + l.color.g - white[0] - white[1]) / 2;
					combinedColor.b = (materialColor.b + l.color.b - white[0] - white[1]) / 2;

					finalColor.r += vis * combinedColor.r * l.intensity * cosTheta;
					finalColor.g += vis * combinedColor.g * l.intensity * cosTheta;
					finalColor.b += vis * combinedColor.b * l.intensity * cosTheta;
				}
			}
			/*else
			{
				shadowDirection.normalize();
				shadowRay.direction = shadowDirection;
				shadowRay.origin = finalInterception;
				intercepted = shadowRay.interceptsWith(blockTriangle, &shadowRayInterception);
				if (!intercepted)
				{

					vis = 1;
					materialColor = nearestMaterial->getDiffuseColor();
					white[0] = std::min(materialColor.r, std::min(materialColor.g, materialColor.b));
					white[1] = std::min(l.color.r, std::min(l.color.g, l.color.b));

					combinedColor.r = (materialColor.r + l.color.r - white[0] - white[1]) / 2;
					combinedColor.g = (materialColor.g + l.color.g - white[0] - white[1]) / 2;
					combinedColor.b = (materialColor.b + l.color.b - white[0] - white[1]) / 2;

					finalColor.r += vis * combinedColor.r * l.intensity;
					finalColor.g += vis * combinedColor.g * l.intensity;
					finalColor.b += vis * combinedColor.b * l.intensity;
				}
			}
		}
		return finalColor;
	}
	else
	{
		return SDL_Color{ 0,0,0,1 };
	}
	/*
		float mult = std::max(0.0F, (1 - nearestDistance / mainCamera.getViewDistance()));

		color.r = mult * color.r;
		color.g = mult * color.g;
		color.b = mult * color.b;


}
*/

