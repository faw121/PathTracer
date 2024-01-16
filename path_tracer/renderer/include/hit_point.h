# pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

struct HitPoint
{
    bool m_is_hit {false};
    bool m_front_face {false};
    glm::vec3 m_hit_point {0.f};
    glm::vec3 m_normal {0.f};
    glm::vec4 m_color {0.f};
};