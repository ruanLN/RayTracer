#ifndef POINT3D_H
#define POINT3D_H

#include "vector3d.h"



class Point3D
{
public:
    Point3D();
    Point3D(double _x, double _y, double _z);

    Vector3D operator-(Point3D other);
    Point3D operator+(Vector3D other);
    Point3D operator-(Vector3D other);

    Vector3D toVector() const;

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Point3D& vec)
    {
        stream << vec.toString();
        return stream;
    }
private:
    double x, y, z;
};

#endif // POINT3D_H
