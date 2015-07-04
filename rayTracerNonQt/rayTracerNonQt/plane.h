#ifndef PLANE_H
#define PLANE_H

#include "drawableobject.h"



class Plane : public DrawableObject
{
public:
    Plane();

    virtual Intersection hitTest(Ray ray, bool *success);
    virtual Color mapTexture(Point3D point);

    Vector3D getNormal() const;
    void setNormal(const Vector3D &value);

    Point3D getPoint() const;
    void setPoint(const Point3D &value);

private:
    Vector3D normal;
    Point3D point;
};

#endif // PLANE_H
