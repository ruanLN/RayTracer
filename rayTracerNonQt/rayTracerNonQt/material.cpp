#include "material.h"

Material::Material()
{

}
Color Material::getMaterialColor() const
{
    return materialColor;
}

void Material::setMaterialColor(const Color &value)
{
    materialColor = value;
}
double Material::getAmbientComponent() const
{
    return ambientComponent;
}

void Material::setAmbientComponent(double value)
{
    ambientComponent = value;
}
double Material::getDiffuseComponent() const
{
    return diffuseComponent;
}

void Material::setDiffuseComponent(double value)
{
    diffuseComponent = value;
}
double Material::getSpecularComponent() const
{
    return specularComponent;
}

void Material::setSpecularComponent(double value)
{
    specularComponent = value;
}
double Material::getSpecularExponent() const
{
    return specularExponent;
}

void Material::setSpecularExponent(double value)
{
    specularExponent = value;
}






