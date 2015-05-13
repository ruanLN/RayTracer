#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "drawableobject.h"

class Triangle : public DrawableObject
{
public:
    Triangle();

    virtual Intersection hitTest(Ray ray, bool *success);

    Point3D getV0() const;
    void setV0(const Point3D &value);

    Point3D getV1() const;
    void setV1(const Point3D &value);

    Point3D getV2() const;
    void setV2(const Point3D &value);

private:
    Point3D v0, v1, v2;
};

#endif // TRIANGLE_H
