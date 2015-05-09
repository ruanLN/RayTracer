#include "color.h"
#include <sstream>

Color::Color() :
    R(0),
    G(0),
    B(0)
{

}

Color::Color(double red, double green, double blue) :
    R(red),
    G(green),
    B(blue)
{

}

Color Color::operator+(Color other)
{
    Color result;
    result.setR(this->R + other.getR());
    result.setG(this->G + other.getG());
    result.setB(this->B + other.getB());
    return result;
}

Color Color::operator*(Color colorFactor)
{
    Color result;
    result.setR(this->R * colorFactor.getR());
    result.setG(this->G * colorFactor.getG());
    result.setB(this->B * colorFactor.getB());
    return result;
}

Color Color::operator*(double factor)
{
    Color result;
    result.setR(this->R * factor);
    result.setG(this->G * factor);
    result.setB(this->B * factor);
    return result;
}

void Color::normalize(double normalizeFactor)
{
    this->R = this->R / normalizeFactor;
    this->G = this->G / normalizeFactor;
    this->B = this->B / normalizeFactor;
}

void Color::clamp()
{
    this->R = (this->R < 0)? 0 : (this->R > 1.0)? 1.0 : this->R;
    this->G = (this->G < 0)? 0 : (this->G > 1.0)? 1.0 : this->G;
    this->B = (this->B < 0)? 0 : (this->B > 1.0)? 1.0 : this->B;
}

double Color::getHighestComponent()
{
    if(this->R > this->G) {
        if(this->R > this->B) {
            return this->R;
        }
        return this->B;
    }
    if(this->G > this->B) {
        return this->G;
    }
    return this->B;
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




