#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "Vector3.h"

class Camera
{
	static constexpr float PI = 3.14;

public:
	inline const Vector3& getPosition() const { return pos; }
	inline void setPosition(const Vector3& pos) { this->pos = pos; }

	inline float getHorizontalFOV() const { return horizontalFov; }
	inline void setHorizontalFOV(float f) { horizontalFov = f; }
	
	inline float getVerticalFOV() const { return verticalFov; }
	inline void setVerticalFOV(float f) { verticalFov = f; }

private:
	Vector3 pos = Vector3(0, 0, 0);

	float horizontalFov = PI * 0.9;
	float verticalFov = PI * 0.9;
};

#endif // CAMERA_H