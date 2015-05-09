#include "point3d.h"

Point3D::Point3D()
{

}

Point3D::Point3D(double _x, double _y, double _z) :
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

double Point3D::getX() const
{
    return x;
}

void Point3D::setX(double value)
{
    x = value;
}
double Point3D::getY() const
{
    return y;
}

void Point3D::setY(double value)
{
    y = value;
}
double Point3D::getZ() const
{
    return z;
}

void Point3D::setZ(double value)
{
    z = value;
}

std::string Point3D::toString() const
{
    std::ostringstream stringStream;
    stringStream << "( " << this->x << ", " << this->y << ", " << this->z << ")";
    std::string stringPoint = stringStream.str();
    return stringPoint;
}




