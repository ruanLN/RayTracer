#ifndef COLOR_H
#define COLOR_H
#include <list>

class Color
{
public:
    Color();
    Color(int red, int green, int blue);

    static std::list<Color> nomalizeColors(std::list<Color> colorList);

    int getB() const;
    void setB(int value);

    int getG() const;
    void setG(int value);

    int getR() const;
    void setR(int value);

private:
    int R, G, B; //or float R, G, B;
};

#endif // COLOR_H
