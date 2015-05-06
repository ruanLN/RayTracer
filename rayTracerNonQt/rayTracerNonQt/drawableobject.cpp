#include "drawableobject.h"

DrawableObject::DrawableObject()
{

}
Material DrawableObject::getObjectMaterial() const
{
    return objectMaterial;
}

void DrawableObject::setObjectMaterial(const Material &value)
{
    objectMaterial = value;
}

Color DrawableObject::getPointColor(Intersection intersection)
{
    return objectMaterial.getMaterialColor();
}

std::string DrawableObject::toString() const
{
    std::ostringstream stringStream;
    stringStream << "Material: " << this->objectMaterial.toString();
    std::string stringPoint = stringStream.str();
    return stringPoint;
}
