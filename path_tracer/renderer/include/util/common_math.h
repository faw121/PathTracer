#pragma once

#include <cmath>
#include <corecrt_math.h>
#include <glm/exponential.hpp>
#include <glm/geometric.hpp>
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

inline glm::vec3 randomInUnitDisk()
{
    glm::vec3 v;
    do {
        v = glm::vec3{randomFloat(-1.f, 1.f),
            randomFloat(-1.f, 1.f), 0.f};
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
    return glm::pow(color, glm::vec3{1/2.2f});
}

inline glm::vec3 reflect(const glm::vec3& i, const glm::vec3& n)
{
    return i - 2.f * glm::dot(i, n) * n;
}

inline glm::vec3 refract(const glm::vec3& i, const glm::vec3& n, float ni_over_no)
{
    float cos_theta = fmin(glm::dot(-i, n), 1.f);
    auto perp = ni_over_no * (i + cos_theta * n);
    // need fabs here, otherwise there will be black points
    auto parallel = -glm::sqrt(fabs(1.f - glm::length2(perp))) * n;
    return perp + parallel;
}