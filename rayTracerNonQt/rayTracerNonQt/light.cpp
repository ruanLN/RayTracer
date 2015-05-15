#include "light.h"

Light::Light() :
    linearAtt(0),
    quadraticAtt(0)
{

}

Light::Light(Point3D p, Color c) :
    position(p),
    color(c),
    linearAtt(0),
    quadraticAtt(0)
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

double Light::getLinearAtt() const
{
    return linearAtt;
}

void Light::setLinearAtt(double value)
{
    linearAtt = value;
}

double Light::getQuadraticAtt() const
{
    return quadraticAtt;
}

void Light::setQuadraticAtt(double value)
{
    quadraticAtt = value;
}

std::string Light::toString() const
{
    std::ostringstream stringStream;
    stringStream << "Pos: " << this->position.toString() << ", color: " << this->color.toString() << ", linear attenuation factor: " << this->linearAtt << ", quadratic attenuation factor: " << this->quadraticAtt;
    std::string stringPoint = stringStream.str();
    return stringPoint;
}



