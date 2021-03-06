#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"



class Material
{
public:
    Material();

    Color getMaterialColor() const;
    void setMaterialColor(const Color &value);

    double getAmbientComponent() const;
    void setAmbientComponent(double value);

    double getDiffuseComponent() const;
    void setDiffuseComponent(double value);

    double getSpecularComponent() const;
    void setSpecularComponent(double value);

    double getSpecularExponent() const;
    void setSpecularExponent(double value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Material& mat)
    {
        stream << mat.toString();
        return stream;
    }
private:
    Color materialColor;
    double ambientComponent, diffuseComponent, specularComponent;
    double specularExponent;
};

#endif // MATERIAL_H
