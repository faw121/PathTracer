# pragma once

#include <util/common_math.h>
#include <util/interval.h>
#include <ray.h>

#include <memory>

#define T_NEAR 0.001f

class Material;

struct HitPoint
{
    float m_t {0.f};
    bool m_front_face {false};
    glm::vec3 m_hit_point_pos {0.f};
    glm::vec3 m_normal {0.f};
    glm::vec3 m_debug_out_normal {0.f};
    std::shared_ptr<Material> m_material {nullptr};

    void setFaceNormal(const Ray& ray, const glm::vec3& norm)
    {   
        m_debug_out_normal = m_normal = norm;

        if (glm::dot(norm, ray.direction()) < 0)
            m_front_face = true;

        else {
            m_normal = -m_normal;
            m_front_face = false;
        }
    }
};

class Hittable
{   
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, HitPoint& hit_point, Interval t_interval=Interval(T_NEAR, INF)) = 0;

    bool rootWithinRange(float root, float t_min, float t_max) { return (root > t_min) && (root < t_max); }
};