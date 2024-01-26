#pragma once

#include "glm/exponential.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include <random>
#include <iostream>
#include <format>


#define INF std::numeric_limits<float>::infinity()

inline float randomFloat()
{
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    return distribution(generator);
}

inline float randomFloat(float min, float max)
{
    return min + (max - min) * randomFloat();
}

inline glm::vec3 randomInUnitSphere()
{   
    glm::vec3 v;
    do {
        v = glm::vec3{randomFloat(-1.f, 1.f),
            randomFloat(-1.f, 1.f), randomFloat(-1.f, 1.f)};
    } while (glm::length2(v) > 1.f);
    
    return v;
}

inline glm::vec3 randomUnitVector()
{
    return glm::normalize(randomInUnitSphere());
}

inline glm::vec3 randomOnHemiSphere(const glm::vec3& normal)
{
    auto u = randomUnitVector();

    if (glm::dot(u, normal) <= 0.f)
        return -u;
    
    return u;
}

inline glm::vec3 linearToGamma(glm::vec3& color)
{
    return glm::sqrt(color);
}