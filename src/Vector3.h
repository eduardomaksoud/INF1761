#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

struct Vector3
{
    float x;
    float y;
    float z;

    Vector3(float x = 0, float y = 0,; float z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3 operator+(Vector3& v)
    {
        Vector3 ret;
        ret.x = this->x + v.x;
        ret.y = this->y + v.y;
        ret.z = this->z + v.z;
        return ret;
    }

    Vector3 operator-(Vector3& v)
    {
        Vector3 ret;
        ret.x = this->x - v.x;
        ret.y = this->y - v.y;
        ret.z = this->z - v.z;
        return ret;
    }

    Vector3 operator*(float k)
    {
        Vector3 ret;
        ret.x = this->x * k;
        ret.y = this->y * k;
        ret.z = this->z * k;
        return ret;
    }

    float dot(Vector3& v)
    {
        float f;

        f = x*v.x + y*v.y + z*v.z;

        return f;
    }

    float norm()
    {
        float f;

        f = std::sqrt(x*x + y*y + z*z);

        return f;
    }
}

#endif // VECTOR3_H
