#include "color.h"

Color::Color()
{

}

Color::Color(int red, int green, int blue) :
    R(red),
    G(green),
    B(blue)
{

}

std::list<Color> Color::nomalizeColors(std::list<Color> colorList)
{
    std::list<Color> normalizedColorList = colorList;
    return normalizedColorList;//mock
}

int Color::getB() const
{
    return B;
}

void Color::setB(int value)
{
    B = value;
}

int Color::getG() const
{
    return G;
}

void Color::setG(int value)
{
    G = value;
}

int Color::getR() const
{
    return R;
}

void Color::setR(int value)
{
    R = value;
}




