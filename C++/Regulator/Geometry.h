#pragma once

struct sPos 
{
    sPos()
        : m_x(0), m_y(0)
    { }
    sPos(int x, int y)
        : m_x(x), m_y(y)
    { }

    int m_x;
    int m_y;
};

struct sSize 
{
    sSize()
        : m_width(0), m_height(0)
    { } 
    sSize(int w, int h)
        : m_width(w), m_height(h)
    { }

    int m_width;
    int m_height;
};

// Верхний левый угол и размер
struct sRect 
{
    sRect() = default;
    sRect(int x, int y, int w, int h)
        : m_pos(x, y), m_size(w, h)
    { }

    bool intersects(const sRect& other) const 
    {
        auto xIntersects = (m_pos.m_x >= other.m_pos.m_x && m_pos.m_x <= other.m_pos.m_x + other.m_size.m_width)
            || (m_pos.m_x + m_size.m_width >= other.m_pos.m_x && m_pos.m_x <= other.m_pos.m_x + other.m_size.m_width);

        auto yIntersects = (m_pos.m_y >= other.m_pos.m_y && m_pos.m_y <= other.m_pos.m_y + other.m_size.m_height)
            || (m_pos.m_y + m_size.m_height >= other.m_pos.m_y && m_pos.m_y <= other.m_pos.m_y + other.m_size.m_height);

        return xIntersects && yIntersects;
    }

    sPos m_pos;
    sSize m_size;
};
