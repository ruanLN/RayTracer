#include "tringle.h"

Tringle::Tringle()
{

}

Intersection Tringle::hitTest(Ray ray, bool *success)
{
    *success = false;
    Intersection intersection;
    return intersection;
}

Point3D Tringle::getV1() const
{
    return v1;
}

void Tringle::setV1(const Point3D &value)
{
    v1 = value;
}
Point3D Tringle::getV2() const
{
    return v2;
}

void Tringle::setV2(const Point3D &value)
{
    v2 = value;
}
Point3D Tringle::getV3() const
{
    return v3;
}

void Tringle::setV3(const Point3D &value)
{
    v3 = value;
}


