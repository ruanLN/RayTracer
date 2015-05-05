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

Vector3D Point3D::operator-(Point3D other)
{
    Vector3D result;
    result.setX(this->x - other.getX());
    result.setY(this->y - other.getY());
    result.setZ(this->z - other.getZ());
    return result;
}

Point3D Point3D::operator+(Vector3D other)
{
    Point3D result;
    result.setX(this->x + other.getX());
    result.setY(this->y + other.getY());
    result.setZ(this->z + other.getZ());
    return result;
}

Point3D Point3D::operator-(Vector3D other)
{
    Point3D result;
    result.setX(this->x - other.getX());
    result.setY(this->y - other.getY());
    result.setZ(this->z - other.getZ());
    return result;
}

Vector3D Point3D::toVector() const
{
    Vector3D result(this->x, this->y, this->z);
    return result;
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




