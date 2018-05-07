#ifndef APPLICATION_IMAGE_IO
#define APPLICATION_IMAGE_IO

#include <string>

namespace Application
{
    class Image;

    class ImageIO
    {
        ImageIO() = delete;
        ImageIO(const ImageIO& imageIO) = delete;
        ~ImageIO() = delete;

      public:
        static Image loadPGM(const std::string& filePath);
        static bool savePGM(const std::string& filePath, const Image& image);
    };
}

#endif // APPLICATION_IMAGE_IO
