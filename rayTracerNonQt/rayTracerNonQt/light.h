#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "point3d.h"


class Light
{
public:
    Light();
    Light(Point3D p, Color c);

    Point3D getPosition() const;
    void setPosition(const Point3D &value);

    Color getColor() const;
    void setColor(const Color &value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Light& vec)
    {
        stream << vec.toString();
        return stream;
    }
private:
    Point3D position;
    //Vector3D direction; //non-directional light
    Color color;
};

#endif // LIGHT_H
