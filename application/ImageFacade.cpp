#include "ImageFacade.h"

#include "Image.h"

#include <cassert>

using namespace Application;

void ImageFacade::convolution(Image& image, const Image& kernel)
{
    assert(kernel.getWidth()%2 == 1);
    assert(kernel.getWidth() > 1);
    assert(kernel.getWidth() == kernel.getHeight());

    unsigned offset = (kernel.getWidth() - 1)/2;

    Pixel pixel;
    for (unsigned i = offset; i < image.getHeight() - offset; ++i)
    {
        for (unsigned j = offset; j < image.getWidth() - offset; ++j)
        {
            pixel = 0;
            for (unsigned ik = 0; ik < kernel.getHeight(); ++ik)
            {
                for (unsigned jk = 0; jk < kernel.getWidth(); ++jk)
                {
                    Pixel imagePixel = image[i + ik - offset][j + jk - offset];
                    Pixel kernelPixel = kernel.at(kernel.getHeight() - ik - 1, kernel.getWidth() - jk - 1);
                    pixel += imagePixel*kernelPixel;
                }
            }
            image[i][j] = pixel <= image.getDepth() ? pixel : image.getDepth();
        }
    }
}
