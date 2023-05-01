/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Math
*/

#include "utils/Math.hpp"
#include <random>

Vec3 Math::normalize(const Vec3 &vec)
{
    float len = length(vec);

    if (len == 0)
        return VEC3_ZERO;
    return {vec.x / len, vec.y / len, vec.z / len};
}

float Math::dot(const Vec3 &vec1, const Vec3 &vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float Math::random(const float min, const float max)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::normal_distribution<float> distribution(min, max);

    return distribution(generator);
}

int Math::random(int min, int max)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

Vec3 Math::randomDir()
{
    float x = random(0, 1);
    float y = random(0, 1);
    float z = random(0, 1);

    return normalize(Vec3(x, y, z));
}

float Math::sign(const float val)
{
    return (0 < val) - (val < 0);
}

Vec3 Math::cross(const Vec3 &vec1, const Vec3 &vec2)
{
    return {vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x};
}

double Math::toRad(const double deg)
{
    return deg * M_PI / 180.0;
}

Vec3 Math::lerp(const Vec3 &vec1, const Vec3 &vec2, const float t)
{
    return vec1 + t * (vec2 - vec1);
}

float Math::length(const Vec3 &vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

bool Math::sameSign(const Vec3 &a, const Vec3 &b)
{
    return (a.x * b.x >= 0) && (a.y * b.y >= 0) && (a.z * b.z >= 0);
}

Vec3 Math::proj(const Vec3 &vec1, const Vec3 &vec2)
{
    return dot(vec1, vec2) / dot(vec2, vec2) * vec2;
}
