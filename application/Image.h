#ifndef APPLICATION_IMAGE
#define APPLICATION_IMAGE

namespace Application
{
using Byte = unsigned char;

class Image
{
  public:
    Image();
    Image(unsigned width, unsigned height, Byte* buffer = nullptr);
    Image(const Image& image);
    ~Image();

    unsigned getWidth() const { return m_width; }
    unsigned getHeight() const { return m_height; }

    Byte* getBuffer();

    bool isValid() const { return m_buffer; } 

    class Row
    {
        friend class Image;
      public:
        Byte& operator[](unsigned column);

      private:
        Row(Image& parent);

        Image& m_imageParent;
        unsigned m_row;
    };

    Row& operator[](unsigned row);

  private:
    Row m_row {*this};
    unsigned m_width {0};
    unsigned m_height {0};
    Byte* m_buffer {nullptr};
    bool m_isExternalBuffer {false};
};
}

#endif // APPLICATION_IMAGE
