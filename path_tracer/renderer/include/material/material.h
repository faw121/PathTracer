#pragma once

#include <ray.h>
#include <hittable/hittable.h>
#include <glm/vec3.hpp>

class HitPoint;

class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(
        const Ray& ray_in, const HitPoint& hit_point, glm::vec3& attenuation, Ray& ray_out) = 0;
};