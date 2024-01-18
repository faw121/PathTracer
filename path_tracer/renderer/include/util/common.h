#pragma once

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

#include <random>


#define INF std::numeric_limits<float>::infinity()

inline float randomFloat()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float randomFloat(float min, float max)
{
    return min + (max - min) * randomFloat();
}
