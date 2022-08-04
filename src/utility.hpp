// helper functions
#pragma once

#include <random>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline float min(float a, float b)
{
    return (a < b) ? a : b;
}

inline float max(float a, float b)
{
    return (a > b) ? a : b;
}

// generate random number
inline float random_number_between(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    std::mt19937 generator;
    auto tseed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    generator.seed(tseed);
    return distribution(generator);
}