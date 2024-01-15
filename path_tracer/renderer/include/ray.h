#pragma once

#include "glm/ext/vector_float3.hpp"
#include <glm/vec3.hpp>

class Ray
{
public:
    Ray(glm::vec3 start, glm::vec3 direction): m_start(start), m_direction(direction) {}
    glm::vec3 at(float t) { return m_start + t * m_direction; }
    glm::vec3 start() { return m_start; }
    glm::vec3 direction() { return m_direction; }

private:
    glm::vec3 m_start;
    glm::vec3 m_direction;
};