#pragma once

#include <cmath>
#include <material/material.h>
#include <util/common_math.h>

class Diffuse: public Material
{
public:
    Diffuse(glm::vec3 albedo): m_albedo(albedo) {}
    
    bool scatter(const Ray& ray_in, const HitPoint& hit_point, glm::vec3& attenuation, Ray& ray_out) override
    {
        auto bounce_direction = glm::normalize(hit_point.m_normal + randomUnitVector());
        ray_out = Ray(hit_point.m_hit_point_pos, bounce_direction);
        attenuation = m_albedo;
        return true;
    }

private:
    glm::vec3 m_albedo;
};