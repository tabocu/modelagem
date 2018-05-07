#include "ImageIO.h"

#include "Image.h"

#include <fstream>
#include <iostream>

using namespace Application;

Image ImageIO::loadPGM(const std::string& filePath)
{
    std::ifstream imageStream(filePath);

    if (!imageStream.is_open())
    {
        return {};
    }

    std::string magicNumber;
    imageStream >> magicNumber;

    unsigned width;
    unsigned height;
    unsigned depth;
    imageStream >> width >> height >> depth;

    unsigned length = width*height;
    Pixel* buffer = new Pixel[length];

    for (unsigned i = 0; i < length; ++i)
    {
        imageStream >> buffer[i];
    }

    imageStream.close();

    return Image(width, height, depth, buffer);
}

bool ImageIO::savePGM(const std::string& filePath, const Image& image)
{
    std::ofstream imageStream(filePath);

    if (!imageStream.is_open())
    {
        return false;
    }

    unsigned width = image.getWidth();
    unsigned height = image.getHeight();
    unsigned depth = image.getDepth();

    imageStream << "P2\n";
    imageStream << width << " " << height << "\n";
    imageStream << depth << "\n";

    for (unsigned i = 0; i < height; ++i)
    {
        for (unsigned j = 0; j < width - 1; ++j)
        {
            imageStream << image.at(i, j)<< " ";
        }
        imageStream << image.at(i, width - 1);
        imageStream << "\n";
    }

    imageStream.close();
    return true;
}
