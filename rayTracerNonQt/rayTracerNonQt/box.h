#ifndef BOX_H
#define BOX_H

#include "drawableobject.h"



class Box : public DrawableObject
{
public:
    Box();

    virtual Intersection hitTest(Ray ray, bool *success);
    virtual Color mapTexture(Point3D point);

    Point3D getP0() const;
    void setP0(const Point3D &value);

    Point3D getP1() const;
    void setP1(const Point3D &value);

private:
    Point3D p0, p1;
    Vector3D rotationVector;
    double rotationAngle;
};

#endif // BOX_H
