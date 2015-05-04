#ifndef SPHERE_H
#define SPHERE_H

#include "drawableobject.h"

class Sphere : public DrawableObject
{
public:
    Sphere();

    virtual Intersection hitTest(Ray ray, bool *success);

    Point3D getCenter() const;
    void setCenter(const Point3D &value);

    double getRay() const;
    void setRay(double value);

private:
    Point3D center;
    double ray;
};

#endif // SPHERE_H
