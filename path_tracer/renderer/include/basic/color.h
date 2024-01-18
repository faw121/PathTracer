#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <array>
#include <stdint.h>

struct Color
{
    uint8_t r {};
    uint8_t g {};
    uint8_t b {};
    uint8_t a {255};

    Color() = default;

    Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255) : r(r_), g(g_), b(b_), a(a_) {}

    Color(std::array<float, 4> color) :
        r(static_cast<uint8_t>(255.f * color[0])), g(static_cast<uint8_t>(255.f * color[1])),
        b(static_cast<uint8_t>(255.f * color[2])), a(static_cast<uint8_t>(255.f * color[3]))
    {}

    Color(glm::vec4 color) :
        r(static_cast<uint8_t>(255.f * color.x)), g(static_cast<uint8_t>(255.f * color.y)),
        b(static_cast<uint8_t>(255.f * color.z)), a(static_cast<uint8_t>(255.f * color.w))
    {}

    Color(std::array<float, 3> color) :
        r(static_cast<uint8_t>(255.f * color[0])), g(static_cast<uint8_t>(255.f * color[1])),
        b(static_cast<uint8_t>(255.f * color[2]))
    {}

    Color(glm::vec3 color) :
        r(static_cast<uint8_t>(255.f * color.x)), g(static_cast<uint8_t>(255.f * color.y)),
        b(static_cast<uint8_t>(255.f * color.z))
    {}
};