#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "drawableobject.h"

class Triangle : public DrawableObject
{
public:
    Triangle();

    virtual Intersection hitTest(Ray ray, bool *success);
    virtual Color mapTexture(Point3D point);

    Point3D getV1() const;
    void setV1(const Point3D &value);

    Point3D getV2() const;
    void setV2(const Point3D &value);

    Point3D getV3() const;
    void setV3(const Point3D &value);

private:
    Point3D v1, v2, v3;
};

#endif // TRIANGLE_H
