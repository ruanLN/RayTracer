#include "color.h"
#include <sstream>

Color::Color()
{

}

Color::Color(double red, double green, double blue) :
    R(red),
    G(green),
    B(blue)
{

}

void Color::normalize(double normalizeFactor)
{
    this->R = this->R / normalizeFactor;
    this->G = this->G / normalizeFactor;
    this->B = this->B / normalizeFactor;
}

std::list<Color> Color::nomalizeColors(std::list<Color> colorList)
{
    std::list<Color> normalizedColorList = colorList;
    return normalizedColorList;//mock
}

double Color::getB() const
{
    return B;
}

void Color::setB(double value)
{
    B = value;
}

double Color::getG() const
{
    return G;
}

void Color::setG(double value)
{
    G = value;
}

double Color::getR() const
{
    return R;
}

void Color::setR(double value)
{
    R = value;
}

std::string Color::toString() const
{
    std::ostringstream stringStream;
    stringStream << "( " << this->R << ", " << this->G << ", " << this->B << ")";
    std::string stringPoint = stringStream.str();
    return stringPoint;
}




