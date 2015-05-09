#include "ray.h"

Ray::Ray()
{

}
Point3D Ray::getOrigin() const
{
    return origin;
}

void Ray::setOrigin(const Point3D &value)
{
    origin = value;
}
Vector3D Ray::getDirection() const
{
    return direction;
}

void Ray::setDirection(const Vector3D &value)
{
    direction = value;
}



