#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"



class Material
{
public:
    Material();

    Color getDiffuseMaterialColor() const;
    void setDiffuseMaterialColor(const Color &value);

    Color getSpecularMaterialColor() const;
    void setSpecularMaterialColor(const Color &value);

    Color getAmbientMaterialColor() const;
    void setAmbientMaterialColor(const Color &value);

    double getAmbientComponent() const;
    void setAmbientComponent(double value);

    double getDiffuseComponent() const;
    void setDiffuseComponent(double value);

    double getSpecularComponent() const;
    void setSpecularComponent(double value);

    double getSpecularExponent() const;
    void setSpecularExponent(double value);

    double getReflectionComponent() const;
    void setReflectionComponent(double value);

    double getTransmissionComponent() const;
    void setTransmissionComponent(double value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Material& mat)
    {
        stream << mat.toString();
        return stream;
    }
private:
    Color diffuseMaterialColor, specularMaterialColor, ambientMaterialColor;
    double ambientComponent, diffuseComponent, specularComponent;
    double specularExponent;
    double reflectionComponent, transmissionComponent;
};

#endif // MATERIAL_H
