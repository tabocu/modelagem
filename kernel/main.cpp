#include <ctime>
#include <iostream>

#pragma GCC push_options
#pragma GCC optimize ("O0")

void runKernel(unsigned long imageWidth,
               unsigned long imageHeight,
               unsigned long kernelWidth,
               unsigned long kernelHeight,
               unsigned *out)
{
    unsigned long image = imageWidth*imageHeight;
    unsigned long kernel = kernelWidth*kernelHeight;
    for (unsigned i = 0; i < image - 1; ++i)
    {
        for (unsigned k = 0; k < kernel; ++k)
        {
            // Each cicle has a comparation
            out[i] = out[i] < i ? 100 : 1000; 

            // Each cycle has to read 3 times 
            for (unsigned c = 0; c < 2; ++c)
            {
                out[i] = out[i]*i;
                out[i] = out[i] - i;
                out[i] = out[i] < i ? 100 : 1000; 
                out[i] = out[i] > i ? 100 : 1000; 
            }
            
            // Each cycle perform the following operations
            out[i] = out[i]*i;
            for (unsigned c = 0; c < 9; ++c)
            {
                out[i] = out[i] - i;
            }

        }
        // for each pixel has to write one time
        out[i] = out[i]*i;
        out[i] = out[i] - i;
        out[i] = out[i] < i ? 100 : 1000; 
        out[i] = out[i] > i ? 100 : 1000; 

        //for each pixel perform the following operations
        out[i] = out[i] - i;
        out[i] = out[i] < i ? 100 : 1000; 
        out[i] = out[i] > i ? 100 : 1000; 
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "\nWrong arguments.\n\n";
        return 1;
    }

    const std::string mode(argv[1]);
    if (mode == "-k" && argc == 6)
    {
        const std::string imageWidthStr(argv[2]);
        const std::string imageHeightStr(argv[3]);
        const std::string kernelWidthStr(argv[4]);
        const std::string kernelHeightStr(argv[5]);
        try
        {
            const unsigned long imageWidth = std::stoul(imageWidthStr, nullptr);
            const unsigned long imageHeight = std::stoul(imageHeightStr, nullptr);
            const unsigned long kernelWidth = std::stoul(kernelWidthStr, nullptr);
            const unsigned long kernelHeight = std::stoul(kernelHeightStr, nullptr);

            unsigned* out = new unsigned[imageWidth*imageHeight];
            clock_t begin = clock();
            runKernel(imageWidth, imageHeight, kernelWidth, kernelHeight, out);
            clock_t end = clock();
            delete[] out;

            std::cout << "CPU Time: " << end - begin << std::endl;
        }
        catch (const std::exception&)
        {
            std::cerr << "\nWrong arguments.\n\n";
            return 2;
        }
    }
    else
    {
        std::cerr << "\nWrong arguments.\n\n";
        return 3;
    }

    return 0;
}
#pragma GCC pop_options
