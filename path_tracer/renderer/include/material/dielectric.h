#pragma once

#include <cmath>
#include <glm/geometric.hpp>
#include <material/material.h>
#include <util/common_math.h>

class Dielectric : public Material
{
public:
    Dielectric(float index_refraction) : m_index_refraction(index_refraction) {}

    bool scatter(const Ray& ray_in, const HitPoint& hit_point, glm::vec3& attenuation, Ray& ray_out) override
    {
        attenuation      = glm::vec3(1.f);
        float ni_over_no = hit_point.m_front_face ? (1.f / m_index_refraction) : m_index_refraction;

        auto cos_theta_i = fmin(glm::dot(-ray_in.direction(), hit_point.m_normal), 1.f); // sign!
        auto sin_theta_i = glm::sqrt(1.f - cos_theta_i * cos_theta_i); // fmin, so do not need fabs
        bool cannot_refract = ni_over_no * sin_theta_i > 1.f;

        glm::vec3 out_direction;
        auto in_direction = glm::normalize(ray_in.direction());

        if (cannot_refract || randomFloat() < reflectance(cos_theta_i, ni_over_no))
            out_direction = glm::reflect(in_direction, hit_point.m_normal);
        else
            out_direction = glm::refract(in_direction, hit_point.m_normal, ni_over_no);

        ray_out = Ray(hit_point.m_hit_point_pos, out_direction);

        return true;
    }

private:
    float m_index_refraction;

    static float reflectance(float cos_theta, float ni_over_no)
    {
        auto r0 = (1.f - ni_over_no) / (1.f + ni_over_no);
        r0 *= r0;
        return r0 + (1.f - r0) * pow(1 - cos_theta, 5.f);
    }
};