#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() = default;

	Vector3(float x, float y = 0, float z = 0)
		: x(x), y(y), z(z)
	{
	}

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	Vector3 operator*(float k) const
	{
		return Vector3(this->x * k, this->y * k, this->z * k);
	}

	Vector3 operator/(float k) const
	{
		return Vector3(this->x / k, this->y / k, this->z / k);
	}

	float dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	float norm() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize()
	{
		float n = norm();
		this->x /= n;
		this->y /= n;
		this->z /= n;
	}

	Vector3 getNormalized() const
	{
		return (*this) / norm();
	} 

	Vector3 cross(const Vector3& v) const
	{
		return Vector3(
			this->y * v.z - this->z * v.y, // X
			this->x * v.z - this->z * v.x, // Y
			this->x * v.y - this->y * v.x  // Z
		);
	}

	void rotate(const Vector3& k, float theta)
	{
		float cosTheta = std::cos(theta);
		float sinTheta = std::sin(theta);

		*this = (*this * cosTheta) + (k.cross(*this) * sinTheta) + (k * k.dot(*this)) * (1 - cosTheta);
	}

	Vector3 getRotated(const Vector3& k, float theta) const
	{
		Vector3 ret;
		float cosTheta = std::cos(theta);
		float sinTheta = std::sin(theta);

		ret = (*this * cosTheta) + (k.cross(*this) * sinTheta) + (k * k.dot(*this)) * (1 - cosTheta);
		return ret;
	}
};

inline Vector3 operator*(float k, const Vector3& vec)
{
	return vec * k;
}

#endif // VECTOR3_H
