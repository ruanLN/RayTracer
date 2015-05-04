#ifndef RAY_H
#define RAY_H

#include "point3d.h"
#include "vector3d.h"

class Ray
{
public:
    Ray();

    Point3D getOrigin() const;
    void setOrigin(const Point3D &value);

    Vector3D getDirection() const;
    void setDirection(const Vector3D &value);

private:
    Point3D origin;
    Vector3D direction;
};

#endif // RAY_H
