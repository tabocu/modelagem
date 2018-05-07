#include "Image.h"

#include <algorithm>
#include <stdexcept>

using namespace Application;

namespace
{
void checkRange(unsigned row, unsigned column, const Image& image)
{
    if(column >= image.getWidth())
    {
        throw std::out_of_range("Column of image is out of range!");
    }

    if(row >= image.getHeight())
    {
        throw std::out_of_range("Row of image is out of range!");
    }
}
}

Image::Image()
    : m_width(0)
    , m_height(0)
    , m_depth(0)
    , m_buffer(nullptr)
    , m_isExternalBuffer(false)
{}

Image::Image(unsigned width,
             unsigned height,
             unsigned depth,
             Pixel* buffer)
    : m_width(width)
    , m_height(height)
    , m_depth(depth)
    , m_buffer(buffer ? buffer : new Pixel[m_width*m_height])
    , m_isExternalBuffer(buffer)
{}

Image::Image(const Image& image)
    : m_width(image.m_width)
    , m_height(image.m_height)
    , m_depth(image.m_depth)
    , m_buffer(new Pixel[m_width*m_height])
    , m_isExternalBuffer(false)
{
    std::copy(image.m_buffer, image.m_buffer + m_width*m_height, m_buffer);
}

Image::~Image()
{
    if (!m_isExternalBuffer)
    {
        delete[] m_buffer;
    }
}

Pixel* Image::getBuffer()
{
    m_isExternalBuffer = true;
    return m_buffer;
}

Image::Row& Image::operator[](unsigned row)
{
    m_row.m_row = row;
    return m_row;
}

Pixel Image::at(unsigned row, unsigned column) const
{
    checkRange(row, column, *this);
    unsigned index = column+row*m_width;
    return m_buffer[index];
}

Image::Row::Row(Image& parent)
    : m_imageParent(parent)
{}

Pixel& Image::Row::operator[](unsigned column)
{
    checkRange(m_row, column, m_imageParent);
    unsigned index = column+m_row*m_imageParent.getWidth();
    return m_imageParent.m_buffer[index];
}
