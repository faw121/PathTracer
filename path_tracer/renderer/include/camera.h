#pragma once

#include <util/common_math.h>

class Camera
{
public:
    float m_fov {glm::radians(45.f)};
    float m_asp {16.f / 9.f};
    float m_focal_length {1.f}; 
    glm::vec3 m_position {0.f, 0.f, 0.f};
    glm::vec3 m_forward {0.f, 0.f, -1.f};
    glm::vec3 m_up {0.f, 0.f, 1.f};
};