#include "point3d.h"

Point3D::Point3D()
{

}

Point3D::Point3D(int _x, int _y, int _z) :
    x(_x),
    y(_y),
    z(_z)
{

}
int Point3D::getX() const
{
    return x;
}

void Point3D::setX(int value)
{
    x = value;
}
int Point3D::getY() const
{
    return y;
}

void Point3D::setY(int value)
{
    y = value;
}
int Point3D::getZ() const
{
    return z;
}

void Point3D::setZ(int value)
{
    z = value;
}




