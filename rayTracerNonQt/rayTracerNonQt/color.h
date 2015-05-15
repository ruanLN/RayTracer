#ifndef COLOR_H
#define COLOR_H
#include <list>
#include <string>
#include <ostream>

class Color
{
public:
    Color();
    Color(double red, double green, double blue);

    Color operator+(Color other);
    Color operator*(Color colorFactor); //parece gamby, mas eh util para luzes
    Color operator*(double factor);
    Color operator/(double factor);

    void normalize(double normalizeFactor);
    void clamp();   //cheaper

    double getHighestComponent();

    double getB() const;
    void setB(double value);

    double getG() const;
    void setG(double value);

    double getR() const;
    void setR(double value);

    //debug purposes
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& stream, const Color& cam)
    {
        stream << cam.toString();
        return stream;
    }
private:
    double R, G, B; //or int R, G, B;
};

#endif // COLOR_H
