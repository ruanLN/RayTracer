#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "point3d.h"
#include "vector3d.h"



class Intersection
{
public:
    Intersection();

    Vector3D getNormalVector() const;
    void setNormalVector(const Vector3D &value);

    Point3D getIntersectionPoint() const;
    void setIntersectionPoint(const Point3D &value);

private:
    Point3D intersectionPoint;
    Vector3D normalVector;
};

#endif // INTERSECTION_H
