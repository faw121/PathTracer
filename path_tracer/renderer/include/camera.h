#pragma once

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <util/common_math.h>
#include <array>

struct ViewPortSize
{
    float m_width {0.f};
    float m_height {0.f};
};

class Camera
{
public:
    static const glm::vec3 WORLD_UP;

    ViewPortSize viewPortSize() const
    {
        auto height = 2 * glm::tan(glm::radians(m_fov / 2.f)) * m_focal_length;
        auto width = height * m_asp;
        return ViewPortSize {width, height};
    }

    float defocusRadius() const { return glm::tan(glm::radians(m_defocus_angle / 2.f)) * m_focal_length; }

    void lookAt(glm::vec3 look_at)
    {
        m_forward = glm::normalize(look_at - m_position);
        m_right = glm::normalize(glm::cross(m_forward, WORLD_UP));
        m_up = glm::cross(m_right, m_forward);
    }

    float m_fov {90.f};
    float m_asp {16.f / 9.f};
    float m_focal_length {1.f}; 
    glm::vec3 m_position {0.f, 0.f, 0.f};
    glm::vec3 m_forward {0.f, 0.f, -1.f};
    glm::vec3 m_up {0.f, 1.f, 0.f};
    glm::vec3 m_right {1.f, 0.f, 0.f};

    float m_defocus_angle {0.f};
};

inline const glm::vec3 Camera::WORLD_UP = {0.f, 1.f, 0.f};