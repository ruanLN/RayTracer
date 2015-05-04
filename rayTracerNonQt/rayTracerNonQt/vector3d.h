#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <ostream>
#include <sstream>

class Vector3D
{
public:
    Vector3D();
    Vector3D(double _x, double _y, double _z);
    Vector3D operator+=(Vector3D& other);
    Vector3D operator-=(Vector3D& other);
    Vector3D operator+(Vector3D& other);
    Vector3D operator-(Vector3D& other);

    double norm();
    static double norm(Vector3D vec);

    void dotProduct(double scalar);
    static Vector3D dotProduct(Vector3D vec, double scalar);

    Vector3D crossProduct(Vector3D other);
    static Vector3D crossProduct(Vector3D vet1, Vector3D vet2);

    void normalize();
    static Vector3D normalize(Vector3D vec);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
    {
        stream << vec.toString();
        return stream;
    }

private:
    double x, y, z;
};

#endif // VECTOR3D_H
