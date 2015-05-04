#include "intersection.h"

Intersection::Intersection()
{

}

Vector3D Intersection::getNormalVector() const
{
    return normalVector;
}

void Intersection::setNormalVector(const Vector3D &value)
{
    normalVector = value;
}
Point3D Intersection::getIntersectionPoint() const
{
    return intersectionPoint;
}

void Intersection::setIntersectionPoint(const Point3D &value)
{
    intersectionPoint = value;
}




