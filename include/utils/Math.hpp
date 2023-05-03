/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** maths
*/

#pragma once

#include "render/Sfml.hpp"
#include "Matrix.hpp"
#include <random>
#include <cmath>

namespace Math
{
    static thread_local std::mt19937 generator(std::random_device{}());
    Vec3 normalize(const Vec3 &vec);
    float dot(const Vec3 &vec1, const Vec3 &vec2);
    float randomf(float min, float max);
    int random(int min, int max);

    Vec3 randomDir();
    float sign(float val);
    Vec3 cross(const Vec3 &vec1, const Vec3 &vec2);
    double toRad(double deg);
    Vec3 lerp(const Vec3 &vec1, const Vec3 &vec2, float t);
    float length(const Vec3 &vec);
    bool sameSign(const Vec3 &a, const Vec3 &b);
    Vec3 proj(const Vec3 &vec1, const Vec3 &vec2);
    Vec3 refract(const Vec3 &incident, const Vec3 &normal, float ior);
    Vec3 reflect(const Vec3 &incident, const Vec3 &normal);
    float fresnel(float cosi, float etai, float etat);
}
