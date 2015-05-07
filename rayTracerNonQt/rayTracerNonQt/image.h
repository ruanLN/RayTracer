#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

class Image
{
public:
    Image();
    Image(int rows, int columns);

    bool writeImage(const std::string& filename);

    Color getPixel(int row, int column);
    void setPixel(int row, int column, Color color);

    int getHeight() const;
    void setHeight(int value);

    int getWidth() const;
    void setWidth(int value);

protected:

    inline int index(int x, int y) const {           //integer index
        return y * width + x;
    }
private:
    int height, width;
    Color *pixels;
};

#endif // IMAGE_H
