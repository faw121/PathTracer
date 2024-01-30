#pragma once
#include "glm/ext/quaternion_geometric.hpp"
#include <util/common_math.h>
#include <material/material.h>
#include <glm/gtc/constants.hpp>

class Metal: public Material
{
public:
    Metal(glm::vec3 albedo, float fuzz): m_albedo(albedo), m_fuzz(fuzz) {}

    bool scatter(const Ray& ray_in, const HitPoint& hit_point, glm::vec3& attenuation, Ray& ray_out) override
    {   
        auto reflected = glm::reflect(ray_in.direction(), hit_point.m_normal);
        m_fuzz = glm::clamp(m_fuzz, 0.f, 1.f);
        reflected = glm::normalize(reflected + m_fuzz * randomUnitVector());
        ray_out = Ray(hit_point.m_hit_point_pos, reflected);
        attenuation = m_albedo;
        return true;
    }
private:
    glm::vec3 m_albedo;
    float m_fuzz;
};