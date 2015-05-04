#ifndef POINT3D_H
#define POINT3D_H

#include "vector3d.h"



class Point3D
{
public:
    Point3D();
    Point3D(int _x, int _y, int _z);

    Vector3D operator-(Point3D other);
    Point3D operator-(Vector3D other);

    Vector3D toVector() const;

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getZ() const;
    void setZ(int value);

private:
    int x, y, z;
};

#endif // POINT3D_H
