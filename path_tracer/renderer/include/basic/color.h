#pragma once

#include "glm/ext/vector_float4.hpp"
#include <array>
#include <glm/vec4.hpp>
#include <stdint.h>
// using Color4f = glm::vec4;
// using Color3f = glm::vec3;
// using Color4i = glm::i8vec4;
// using Color3i = glm::i8vec3; 

struct Color
{
    uint8_t r {};
    uint8_t g {};
    uint8_t b {};
    uint8_t a {255};

    Color() = default;

    Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255): r(r_), g(g_), b(b_), a(a_) {}

    Color(std::array<float, 4> color): r(static_cast<uint8_t>(color[0])), g(static_cast<uint8_t>(color[1])),
        b(static_cast<uint8_t>(color[2])), a(static_cast<uint8_t>(color[3])) {}

    Color(glm::vec4 color): r(static_cast<uint8_t>(color.x)), g(static_cast<uint8_t>(color.y)),
        b(static_cast<uint8_t>(color.y)), a(static_cast<uint8_t>(color.w)) {}
};