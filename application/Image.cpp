#include "Image.h"

#include <algorithm>
#include <stdexcept>

using namespace Application;

Image::Image()
    : m_width(0)
    , m_height(0)
    , m_buffer(nullptr)
    , m_isExternalBuffer(false)
{}

Image::Image(unsigned width, unsigned height, Byte* buffer)
    : m_width(width)
    , m_height(height)
    , m_buffer(buffer ? buffer : new Byte[m_width*m_height])
    , m_isExternalBuffer(buffer)
{}

Image::Image(const Image& image)
    : m_width(image.m_width)
    , m_height(image.m_height)
    , m_buffer(new Byte[m_width*m_height])
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

Byte* Image::getBuffer()
{
    m_isExternalBuffer = true;
    return m_buffer;
}

Image::Row& Image::operator[](unsigned row)
{
    m_row.m_row = row;
    return m_row;
}

Image::Row::Row(Image& parent)
    : m_imageParent(parent)
{}

Byte& Image::Row::operator[](unsigned column)
{
    if(column >= m_imageParent.getWidth())
    {
        throw std::out_of_range("Column of image is out of range!");
    }

    if(m_row >= m_imageParent.getHeight())
    {
        throw std::out_of_range("Row of image is out of range!");
    }

    unsigned index = column+m_row*m_imageParent.getWidth();
    return m_imageParent.m_buffer[index];
}
