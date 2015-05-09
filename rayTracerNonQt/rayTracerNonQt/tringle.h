#ifndef TRINGLE_H
#define TRINGLE_H

#include "drawableobject.h"

class Tringle : public DrawableObject
{
public:
    Tringle();

    virtual Intersection hitTest(Ray ray, bool *success);

    Point3D getV1() const;
    void setV1(const Point3D &value);

    Point3D getV2() const;
    void setV2(const Point3D &value);

    Point3D getV3() const;
    void setV3(const Point3D &value);

private:
    Point3D v1, v2, v3;
};

#endif // TRINGLE_H
