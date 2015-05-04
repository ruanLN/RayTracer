#ifndef COLOR_H
#define COLOR_H
#include <list>

class Color
{
public:
    Color();
    Color(double red, double green, double blue);

    void normalize(double normalizeFactor);

    static std::list<Color> nomalizeColors(std::list<Color> colorList);

    double getB() const;
    void setB(double value);

    double getG() const;
    void setG(double value);

    double getR() const;
    void setR(double value);

private:
    double R, G, B; //or int R, G, B;
};

#endif // COLOR_H
