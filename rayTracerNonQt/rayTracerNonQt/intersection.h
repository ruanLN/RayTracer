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

    double getT() const;
    void setT(double value);

private:
    Point3D intersectionPoint;
    Vector3D normalVector;
    double t;
};

#endif // INTERSECTION_H
