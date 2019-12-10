#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Camera.h"
#include "SceneTriangle.h"
#include "SceneSphere.h"
#include "PointLight.h" 
#include "RenderingFrame.h"
#include "Ray.h"

enum class GeometryType
{
	Sphere,
	Triangle
};

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

	const PointLight& getLight(int idx) const
	{
		return lightSources[idx];
	}

	int addLight(const PointLight& l)
	{
		lightSources.push_back(l);
		return lightSources.size() - 1;
	}

private:
	std::vector<SceneTriangle> triangles;
	std::vector<SceneSphere> spheres;
	std::vector<PointLight> lightSources;
	Camera mainCamera;

	void internalRender(RenderingFrame& f, int w, int h, int firstX, int firstY) const;

	//
	//	Performs raytracing with the specified view ray.
	//	Returns the color being reflected by the ray coming from the
	//	opposite direction.
	//
	SDL_Color traceRay(const Ray& ray) const;

	struct RayInterceptionData
	{
		Vector3 interception;		// the interception found
		Vector3 normal;				// the ray's normal with the surface intercepted
		Material* material;	// the intercepted surface's material
		GeometryType geometryType;	// the intercepted surface's geometry type
		float distance;				// the distance from the ray's origin to the intercepted surface
		SphereSide sphereSide;
	};
	void findInterceptionWithSceneObjects(const Ray& ray, RayInterceptionData& ret) const;
};

#endif // SCENE_H