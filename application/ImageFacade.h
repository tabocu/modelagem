#ifndef APPLICATION_IMAGE_FACADE
#define APPLICATION_IMAGE_FACADE

namespace Application
{
    class Image;

    class ImageFacade
    {
        ImageFacade() = delete;
        ImageFacade(const ImageFacade& imageFacade) = delete;
        ~ImageFacade() = delete;

      public:
        static void convolution(Image& image, const Image& kernel);
    };
}

#endif // APPLICATION_IMAGE_FACADE

