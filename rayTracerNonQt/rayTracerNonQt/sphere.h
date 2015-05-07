#ifndef SPHERE_H
#define SPHERE_H

#include "drawableobject.h"

class Sphere : public DrawableObject
{
public:
    Sphere();

    virtual Intersection hitTest(Ray radius, bool *success);
    virtual std::string toString() const;

    Point3D getCenter() const;
    void setCenter(const Point3D &value);

    double getRadius() const;
    void setRadius(double value);

private:
    Point3D center;
    double radius;
};

#endif // SPHERE_H
