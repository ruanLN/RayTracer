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

bool Image::readImage(const std::string &filename) {
    std::vector<unsigned char> image;
    LodePNG::loadFile(image, filename);
    Color *currentPixel = pixels;
    std::vector<unsigned char>::iterator imageIterator = image.begin();
    while (imageIterator != image.end()) {
        currentPixel->setR((*imageIterator) / 255.0);
        imageIterator++;
        currentPixel->setG((*imageIterator) / 255.0);
        imageIterator++;
        currentPixel->setB((*imageIterator) / 255.0);
        imageIterator++;
        imageIterator++;
        currentPixel++;
    }

}

Image &Image::normalizeImageColor(double factor)
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            Color c = getPixel(i, j);
            c.normalize(factor);
            setPixel(i, j, c);
        }
    }
    return (*this);
}

Color Image::getPixel(int row, int column)
{
    return pixels[index(row, column)];
}

Color Image::getPixel(float row, float column)
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



