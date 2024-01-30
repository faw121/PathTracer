#pragma once

#include <memory>
#include <util/common_math.h>
#include <hittable/hittable.h>
#include <ray.h>


class Sphere: public Hittable
{
public:
    glm::vec3 m_center {0.f, 0.f, 0.f};
    float m_radius {1.f};
    std::shared_ptr<Material> m_material {nullptr};

    Sphere() = default;
    
    Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material): 
        m_center(center), m_radius(radius), m_material(material) {}

    // v^2t^2 + 2v(A-C)t + (A-C)^2 - r^2 = 0
    bool hit(const Ray& ray, HitPoint& hit_point, Interval t_interval=Interval(T_NEAR, INF)) override
    {
        auto ca = ray.start() - m_center;

        float a = glm::dot(ray.direction(), ray.direction());
        float b = 2.f * glm::dot(ray.direction(), ca);
        float c = glm::dot(ca, ca) - m_radius * m_radius;

        float discriminant = b * b - 4.f * a * c;

        float root = 0.f;

        if (discriminant <= 0.f)
            return false;

        float sqrt_d = glm::sqrt(discriminant);
        root = (-b - sqrt_d) / (2.f * a); // near root

        if (!t_interval.surrounds(root)) {
            root = (-b + sqrt_d) / (2.f * a); // far root
            if (!t_interval.surrounds(root))
                return false;
        }
        hit_point.m_t = root;
        hit_point.m_hit_point_pos = ray.at(root);
        auto normal = (hit_point.m_hit_point_pos - m_center) / m_radius; // faster
        hit_point.setFaceNormal(ray, normal);
        hit_point.m_material = m_material;

        return true;
    }
};