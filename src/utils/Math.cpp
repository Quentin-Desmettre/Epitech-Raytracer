/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Math
*/

#include "utils/Math.hpp"

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

float Math::realRandomf(float min, float max)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<float> distribution(min, max);

    return distribution(generator);
}

float Math::randomf(float min, float max)
{
    float theta = realRandomf(0, 1) * 2 * M_PI;
    float rho = sqrt(-2 * std::log(realRandomf(0, 1)));

    return rho * cos(theta) * (max - min) + min;
}

int Math::random(int min, int max)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

Vec3 Math::randomDir(const Vec3 &normal)
{
    Vec3 dir(randomf(-1, 1), randomf(-1, 1), randomf(-1, 1));

    dir = normalize(dir);
    return dir * sign(dot(dir, normal));
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

Vec3 Math::refract(const Vec3 &incident, const Vec3 &normal, float n1, float n2)
{
    float cosi = dot(incident, normal);
    float etai = n1;
    float etat = n2;
    Vec3 n = normal;

    if (cosi < 0)
        cosi = -cosi;
    else {
        std::swap(etai, etat);
        n = -n;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0)
        return VEC3_ZERO;
    return eta * incident + (eta * cosi - sqrtf(k)) * n;
}

float Math::fresnel(float cosi, float etai, float etat)
{
    float r0 = powf((etai - etat) / (etai + etat), 2.0f);
    float x = 1.0f - (cosi < 0 ? -cosi : cosi);
    float fresnel = r0 + (1.0f - r0) * powf(x, 5.0f);
    return fresnel;
}

bool Math::isPowerOfTwo(int n)
{
    return (ceil(log2(n)) == floor(log2(n)));
}

float Math::toRad(float deg)
{
    return deg * M_PIf / 180.0f;
}

float Math::toDeg(float rad)
{
    return rad * 180.0f / M_PIf;
}
