# pragma once

#include <common.h>
#include <ray.h>

#include <limits>

const float Infinity = std::numeric_limits<float>::infinity();

struct HitPoint
{
    float m_t {0.f};
    bool m_front_face {false};
    glm::vec3 m_hit_point {0.f};
    glm::vec3 m_normal {0.f};
    glm::vec3 m_color {0.f};

    void setFaceNormal(const Ray& ray, glm::vec3& norm)
    {   
        m_normal = norm;

        if (glm::dot(norm, ray.direction()) < 0)
            m_front_face = true;

        else
            m_normal = -m_normal;
    }
};

class Hittable
{   
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, HitPoint& hit_point, float t_max=Infinity, float t_min=0.001f) = 0;

    bool rootWithinRange(float root, float t_min, float t_max) { return (root > t_min) && (root < t_max); }
};