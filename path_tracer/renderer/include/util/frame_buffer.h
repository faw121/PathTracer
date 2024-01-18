#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>
#include <cassert>

#include <util/color.h>

class FrameBuffer
{
public:
    int width() { return m_w; }
    int height() { return m_h; }

    const uint8_t* data() { return (const uint8_t*)m_pixel_data.data(); } 

    void set(int i, int j, std::array<float, 4 > color )
    {   
        int ind = j * m_w + i;
        assert(ind < m_w * m_h);
        m_pixel_data[ind] = Color(color);
    }

    void set(int i, int j, glm::vec4 color )
    {   
        int ind = j * m_w + i;
        assert(ind < m_w * m_h);
        m_pixel_data[ind] = Color(color);
    }

    void set(int i, int j, std::array<float, 3> color )
    {   
        int ind = j * m_w + i;
        assert(ind < m_w * m_h);
        m_pixel_data[ind] = Color(color);
    }

    void set(int i, int j, glm::vec3 color )
    {   
        int ind = j * m_w + i;
        assert(ind < m_w * m_h);
        m_pixel_data[ind] = Color(color);
    }

    void resetSize(int w, int h)
    {
        m_w = w;
        m_h = h;
        initDataBuffer();
    }

    FrameBuffer(int w, int h): m_w(w), m_h(h)
    {
        initDataBuffer();
    }

private:
    void initDataBuffer()
    {
        m_pixel_data.resize(m_w * m_h);
        std::fill(std::begin(m_pixel_data), std::end(m_pixel_data), Color());
    }

    int m_w;
    int m_h;

    std::vector<Color> m_pixel_data;
};