#include "vector3d.h"

Vector3D::Vector3D()
{

}

Vector3D::Vector3D(int _x, int _y, int _z) :
    x(_x),
    y(_y),
    z(_z)
{

}

Vector3D Vector3D::operator+=(Vector3D &other)
{
    this->x += other.getX();
    this->y += other.getY();
    this->z += other.getZ();
    return (*this);
}

Vector3D Vector3D::operator-=(Vector3D &other)
{
    this->x -= other.getX();
    this->y -= other.getY();
    this->z -= other.getZ();
    return (*this);
}

Vector3D Vector3D::operator+(Vector3D &other)
{
    Vector3D result = *this;
    result += other;
    return result;
}

Vector3D Vector3D::operator-(Vector3D &other)
{
    Vector3D result = *this;
    result -= other;
    return result;
}

std::string Vector3D::toString() const
{
    std::ostringstream stringStream;
    stringStream << "( " << this->x << ", " << this->y << ", " << this->z << ")";
    std::string stringVec = stringStream.str();
    return stringVec;
}

int Vector3D::getX() const
{
    return x;
}

void Vector3D::setX(int value)
{
    x = value;
}
int Vector3D::getY() const
{
    return y;
}

void Vector3D::setY(int value)
{
    y = value;
}
int Vector3D::getZ() const
{
    return z;
}

void Vector3D::setZ(int value)
{
    z = value;
}


