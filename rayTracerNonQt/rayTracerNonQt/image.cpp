#include "image.h"
#include <vector>
#include "png/lodepng.cpp"

Image::Image() :
    height(-1),
    width(-1)
{
    pixels = NULL;
}

Image::Image(int rows, int columns) :
    height(rows),
    width(columns)
{
    pixels = new Color[height*width];
}

bool Image::writeImage(const std::string &filename)
{
    if(!pixels) {
        return false;
    }
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    std::vector<unsigned char>::iterator imageIterator = image.begin();
    Color *currentPixel = pixels;
    while (imageIterator != image.end()) {
        *imageIterator = (unsigned char)(currentPixel->getR() * 255.0);
        imageIterator++;
        *imageIterator = (unsigned char)(currentPixel->getG() * 255.0);
        imageIterator++;
        *imageIterator = (unsigned char)(currentPixel->getB() * 255.0);
        imageIterator++;
        *imageIterator = 255;
        imageIterator++;
        currentPixel++;
    }
    unsigned int encodeReturn = LodePNG::encode(filename, image, width, height);
    return true;
}

Color Image::getPixel(int row, int column)
{
    return pixels[index(row, column)];
}

void Image::setPixel(int row, int column, Color color)
{
    pixels[index(row, column)] = color;
}

int Image::getHeight() const
{
    return height;
}

void Image::setHeight(int value)
{
    height = value;
}
int Image::getWidth() const
{
    return width;
}

void Image::setWidth(int value)
{
    width = value;
}



