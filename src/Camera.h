#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "Vector3.h"

class Camera
{
	static constexpr float PI = 3.14;

public:
	const Vector3& getPosition() const { return pos; }
	void setPosition(const Vector3& pos) { this->pos = pos; }

	const Vector3& getLocalXAxis() const { return localXAxis; }
	const Vector3& getLocalYAxis() const { return localYAxis; }
	const Vector3& getLocalZAxis() const { return localZAxis; }

	void RotateX(float theta)
	{
		localYAxis.rotate(localXAxis, theta);
		localZAxis.rotate(localXAxis, theta);
	}

	void RotateY(float theta)
	{
		localXAxis.rotate(localYAxis, theta);
		localZAxis.rotate(localYAxis, theta);
	}

	void RotateZ(float theta)
	{
		localXAxis.rotate(localZAxis, theta);
		localYAxis.rotate(localZAxis, theta);
	}

	float getHorizontalFOV() const { return horizontalFov; }
	void setHorizontalFOV(float f) { horizontalFov = f; }

	float getVerticalFOV() const { return verticalFov; }
	void setVerticalFOV(float f) { verticalFov = f; }

	float getViewDistance() const { return viewDistance; }

private:
	Vector3 pos = Vector3(0, 0, 0);

	Vector3 localXAxis = Vector3(1, 0, 0);
	Vector3 localYAxis = Vector3(0, 1, 0);
	Vector3 localZAxis = Vector3(0, 0, 1);
	
	float horizontalFov = PI * 0.5;
	float verticalFov = PI * 0.5;

	float viewDistance = 20;
};

#endif // CAMERA_H