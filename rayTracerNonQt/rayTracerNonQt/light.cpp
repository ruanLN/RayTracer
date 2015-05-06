#include "light.h"

Light::Light()
{

}

Light::Light(Point3D p, Color c) :
    position(p),
    color(c)
{

}
Point3D Light::getPosition() const
{
    return position;
}

void Light::setPosition(const Point3D &value)
{
    position = value;
}
Color Light::getColor() const
{
    return color;
}

void Light::setColor(const Color &value)
{
    color = value;
}

std::string Light::toString() const
{
    std::ostringstream ss;
    ss << "Pos: " << this->position.toString() << "; color: " << this->color.toString();
    std::string stringCam = ss.str();
    return stringCam;
}



