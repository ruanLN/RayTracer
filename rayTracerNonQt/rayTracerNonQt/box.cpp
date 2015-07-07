#include "box.h"

Box::Box()
{

}



Intersection Box::hitTest(Ray ray, bool *success)
{
}

Color Box::mapTexture(Point3D point)
{
}
Point3D Box::getP1() const
{
    return p1;
}

void Box::setP1(const Point3D &value)
{
    p1 = value;
}
Point3D Box::getP0() const
{
    return p0;
}

void Box::setP0(const Point3D &value)
{
    p0 = value;
}

