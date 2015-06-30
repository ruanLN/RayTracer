#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

class Image
{
public:
    Image();
    Image(int rows, int columns);

    bool writeImage(const std::string& filename);
    bool readImage(const std::string &filename);

    Image& normalizeImageColor(double factor);

    Color getPixel(int row, int column);
    Color getPixel(float row, float column);
    void setPixel(int row, int column, Color color);

    int getHeight() const;
    void setHeight(int value);

    int getWidth() const;
    void setWidth(int value);

protected:

    inline int index(int y, int x) const {           //integer index
        return y * width + x;
    }

    inline int index(float y, float x) const {
        return (int) (y * width * height + x * width);
    }
private:
    int height, width;
    Color *pixels;
};

#endif // IMAGE_H
