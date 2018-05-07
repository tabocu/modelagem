#ifndef APPLICATION_IMAGE
#define APPLICATION_IMAGE

namespace Application
{
using Pixel = unsigned;

class Image
{
  public:
    Image();
    Image(unsigned width,
          unsigned height,
          unsigned depth,
          Pixel* buffer = nullptr);

    Image(const Image& image);
    ~Image();

    unsigned getWidth() const { return m_width; }
    unsigned getHeight() const { return m_height; }

    unsigned getDepth() const { return m_depth; }

    Pixel* getBuffer();

    bool isValid() const { return m_buffer; } 

    Pixel at(unsigned row, unsigned column) const;

    class Row
    {
        friend class Image;
      public:
        Pixel& operator[](unsigned column);

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
    unsigned m_depth {0};
    Pixel* m_buffer {nullptr};
    bool m_isExternalBuffer {false};
};
}

#endif // APPLICATION_IMAGE
