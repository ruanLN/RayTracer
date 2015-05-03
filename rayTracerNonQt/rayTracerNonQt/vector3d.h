#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <ostream>
#include <sstream>

class Vector3D
{
public:
    Vector3D();
    Vector3D(int _x, int _y, int _z);
    Vector3D operator+=(Vector3D& other);
    Vector3D operator-=(Vector3D& other);
    Vector3D operator+(Vector3D& other);
    Vector3D operator-(Vector3D& other);

    friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
    {
        stream << vec.toString();
        return stream;
    }
    std::string toString() const;

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getZ() const;
    void setZ(int value);

private:
    int x, y, z;
};

#endif // VECTOR3D_H
