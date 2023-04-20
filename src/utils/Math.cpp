/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Math
*/

#include "utils/Math.hpp"

Vec3 Math::normalize(Vec3 vec)
{
    float len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    return Vec3(vec.x / len, vec.y / len, vec.z / len);
}

float Math::dot(Vec3 vec1, Vec3 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float Math::random(float min, float max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}

float Math::randomNormDistrib()
{
    float u1 = random(0, 1);
    float u2 = random(0, 1);
    return sqrt(-2.0f * log(u1)) * cos(2.0f * M_PI * u2);
}

Vec3 Math::randomDir()
{
    float x = randomNormDistrib();
    float y = randomNormDistrib();
    float z = randomNormDistrib();

    return normalize(Vec3(x, y, z));
}

float Math::sign(float val)
{
    return (0 < val) - (val < 0);
}

Vec3 Math::cross(Vec3 vec1, Vec3 vec2)
{
    return Vec3(vec1.y * vec2.z - vec1.z * vec2.y,
                        vec1.z * vec2.x - vec1.x * vec2.z,
                        vec1.x * vec2.y - vec1.y * vec2.x);
}

double Math::toRad(double deg)
{
    return deg * M_PI / 180.0;
}

Vec3 Math::lerp(Vec3 vec1, Vec3 vec2, float t)
{
    return vec1 + t * (vec2 - vec1);
}

float Math::length(Vec3 vec)
{
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

bool Math::sameSign(Vec3 a, Vec3 b)
{
    return (a.x * b.x >= 0) && (a.y * b.y >= 0) && (a.z * b.z >= 0);
}
