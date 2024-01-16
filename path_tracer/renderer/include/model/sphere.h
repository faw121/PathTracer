#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <ray.h>
#include <hit_point.h>

class Sphere
{
public:
    glm::vec3 m_center {0.f, 0.f, 0.f};
    float m_radius {1.f};
    glm::vec4 m_color = {0.8f, 0.7f, 0.2f, 1.f};

    // v^2t^2 + 2v(A-C)t + (A-C)^2 - r^2 = 0
    HitPoint hit(Ray ray)
    {
        auto ca = ray.start() - m_center;

        float a = glm::dot(ray.direction(), ray.direction());
        float b = 2.f * glm::dot(ray.direction(), ca);
        float c = glm::dot(ca, ca) - m_radius * m_radius;

        float discriminant = b * b - 4.f * a * c;

        float root = 0.f;

        HitPoint hit_point;
        hit_point.m_is_hit = false;

        if (discriminant > 0.f) {
            float sqrt_d = glm::sqrt(discriminant);
            root = (-b - sqrt_d) / (2.f * a); // near root

            if (root > 0.001f)
                hit_point.m_is_hit = true;
            else {
                root = (-b + sqrt_d) / (2.f * a); // far root
                if (root > 0.001f)
                    hit_point.m_is_hit = true;
            }
        }
        if (hit_point.m_is_hit) {
            hit_point.m_hit_point = ray.at(root);
            hit_point.m_normal = (hit_point.m_hit_point - m_center) / m_radius; // faster
            if (glm::dot(hit_point.m_normal, ray.direction()) < 0)
                hit_point.m_front_face = true;
            else
                hit_point.m_normal = - hit_point.m_normal;
            hit_point.m_color = m_color;
        }

        return hit_point;
    }
};