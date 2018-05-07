#include "Image.h"
#include "ImageFacade.h"
#include "ImageIO.h"

#include <ctime>
#include <exception>
#include <iostream>

using namespace Application;

void imageGenerator(const std::string& path,
                    unsigned width,
                    unsigned height, 
                    unsigned depth)
{
    Image image(width, height, depth);
    ++depth;

    Pixel pixel = 0;
    for (unsigned i = 0; i < image.getHeight(); ++i)
    {
        for (unsigned j = 0; j < image.getWidth(); j++)
        {
            image[i][j] = (pixel++)%depth;
        }
    }
    ImageIO::savePGM(path, image);
}

void imageConvolution(const std::string& pathImage,
                      const std::string& pathKernel,
                      const std::string& pathSave)
{
    Image image = ImageIO::loadPGM(pathImage);
    Image kernel = ImageIO::loadPGM(pathKernel);

    clock_t begin = clock();
    ImageFacade::convolution(image, kernel);
    clock_t end = clock();

    std::cout << "CPU Time: " << end-begin << std::endl;
    
    ImageIO::savePGM(pathSave, image);
    delete[] image.getBuffer();
    delete[] kernel.getBuffer();
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "\nWrong arguments.\n\n";
        return 1;
    }

    const std::string mode(argv[1]);

    if (mode == "-g" && argc == 6)
    {
        const std::string path(argv[2]);
        const std::string widthStr(argv[3]);
        const std::string heightStr(argv[4]);
        const std::string depthStr(argv[5]);
        try
        {
            const unsigned width = std::stoul(widthStr, nullptr);
            const unsigned height = std::stoul(heightStr, nullptr);
            const unsigned depth = std::stoul(depthStr, nullptr);
            imageGenerator(path, width, height, depth);
        }
        catch (const std::exception&)
        {
            std::cerr << "\nWrong arguments.\n\n";
            return 2;
        }
    }
    else if (mode == "-c" && argc == 5)
    {
        const std::string pathImage(argv[2]);
        const std::string pathKernel(argv[3]);
        const std::string pathSave(argv[4]);
        try
        {
            imageConvolution(pathImage, pathKernel, pathSave);
        }
        catch (const std::exception&)
        {
            std::cerr << "\nWrong arguments.\n\n";
            return 3;
        }
    }
    else
    {
        std::cerr << "\nWrong arguments.\n\n";
        return 4;
    }

    return 0;
}
