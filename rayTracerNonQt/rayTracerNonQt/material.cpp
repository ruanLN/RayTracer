#include "material.h"
#include <sstream>

Material::Material()
{

}
Color Material::getDiffuseMaterialColor() const
{
    return diffuseMaterialColor;
}

void Material::setDiffuseMaterialColor(const Color &value)
{
    diffuseMaterialColor = value;
}

Color Material::getSpecularMaterialColor() const
{
    return specularMaterialColor;
}

void Material::setSpecularMaterialColor(const Color &value)
{
    specularMaterialColor = value;
}

Color Material::getAmbientMaterialColor() const
{
    return ambientMaterialColor;
}

void Material::setAmbientMaterialColor(const Color &value)
{
    ambientMaterialColor = value;
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

std::string Material::toString() const
{
    std::ostringstream stringStream;
    stringStream << "Diffuse color: " << this->diffuseMaterialColor << ", specular color: " << this->specularMaterialColor << ", ambient color: " << this->ambientMaterialColor << ", ka: " << this->ambientComponent << ", kd: " << this->diffuseComponent << ", ks: " << this->specularComponent << ", exp: " << this->specularExponent;
    std::string stringPoint = stringStream.str();
    return stringPoint;
}






