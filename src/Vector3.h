#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float x = 0, float y = 0, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator+(const Vector3& v) const
	{
		Vector3 ret;
		ret.x = this->x + v.x;
		ret.y = this->y + v.y;
		ret.z = this->z + v.z;
		return ret;
	}

	Vector3 operator-(const Vector3& v) const
	{
		Vector3 ret;
		ret.x = this->x - v.x;
		ret.y = this->y - v.y;
		ret.z = this->z - v.z;
		return ret;
	}

	Vector3 operator*(float k) const
	{
		Vector3 ret;
		ret.x = this->x * k;
		ret.y = this->y * k;
		ret.z = this->z * k;
		return ret;
	}

	Vector3 operator/(float k) const
	{
		Vector3 ret;
		ret.x = this->x / k;
		ret.y = this->y / k;
		ret.z = this->z / k;
		return ret;
	}

	float dot(const Vector3& v) const
	{
		float f;

		f = x * v.x + y * v.y + z * v.z;

		return f;
	}

	float norm() const
	{
		float f;

		f = std::sqrt(x * x + y * y + z * z);

		return f;
	}

	Vector3 normalized() const
	{
		return (*this) / norm();
	}

	Vector3 cross(const Vector3& v) const
	{
		return Vector3(
			this->y * v.z - this->z * v.y, // X
			this->z * v.x - this->x * v.z, // Y
			this->x * v.y - this->y * v.x  // Z
		);
	}
};

inline Vector3 operator*(float k, const Vector3& vec)
{
	return vec * k;
}

#endif // VECTOR3_H
