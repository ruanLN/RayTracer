#include "vector3d.h"
#include "cmath"

Vector3D::Vector3D()
{

}

Vector3D::Vector3D(double _x, double _y, double _z) :
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

double Vector3D::norm()
{
    return norm((*this));
}

double Vector3D::norm(Vector3D vec)
{
    return sqrt(vec.getX()*vec.getX() + vec.getY()*vec.getY() + vec.getZ()*vec.getZ());
}

void Vector3D::scalarProduct(double scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}

Vector3D Vector3D::scalarProduct(Vector3D vec, double scalar)
{
    vec.setX(vec.getX() * scalar);
    vec.setY(vec.getY() * scalar);
    vec.setZ(vec.getZ() * scalar);
    return vec;
}

double Vector3D::dotProduct(Vector3D other)
{
    return (this->getX() * other.getX()) + (this->getY() * other.getY()) + (this->getZ() * other.getZ());
}

Vector3D Vector3D::crossProduct(Vector3D other)
{
    Vector3D result;
    result.setX(this->getY() * other.getZ() - this->getZ() * other.getY());
    result.setY(this->getZ() * other.getX() - this->getX() * other.getZ());
    result.setZ(this->getX() * other.getY() - this->getY() * other.getX());
    return result;
}

Vector3D Vector3D::crossProduct(Vector3D vet1, Vector3D vet2)
{
    Vector3D result;
    result.setX(vet1.getY() * vet2.getZ() - vet1.getZ() * vet2.getY());
    result.setY(vet1.getZ() * vet2.getX() - vet1.getX() * vet2.getZ());
    result.setZ(vet1.getX() * vet2.getY() - vet1.getY() * vet2.getX());
    return result;
}

void Vector3D::normalize()
{
    double norm = this->norm();
    this->x = this->x / norm;
    this->y = this->y / norm;
    this->z = this->z / norm;
}

Vector3D Vector3D::normalize(Vector3D vec)
{
    double norm = vec.norm();
    vec.setX(vec.getX() / norm);
    vec.setY(vec.getY() / norm);
    vec.setZ(vec.getZ() / norm);
    return vec;
}

std::string Vector3D::toString() const
{
    std::ostringstream stringStream;
    stringStream << "( " << this->x << ", " << this->y << ", " << this->z << ")";
    std::string stringVec = stringStream.str();
    return stringVec;
}

double Vector3D::getX() const
{
    return x;
}

void Vector3D::setX(double value)
{
    x = value;
}
double Vector3D::getY() const
{
    return y;
}

void Vector3D::setY(double value)
{
    y = value;
}
double Vector3D::getZ() const
{
    return z;
}

void Vector3D::setZ(double value)
{
    z = value;
}


