/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** maths
*/

#pragma once

#include "Sfml.hpp"
#include "Matrix.hpp"
#include <cmath>

namespace Math
{
    Vec3 normalize(const Vec3 &vec);
    float dot(const Vec3 &vec1, const Vec3 &vec2);
    float random(const float min, const float max);
    Vec3 randomDir();
    float sign(float val);
    Vec3 cross(const Vec3 &vec1, const Vec3 &vec2);
    double toRad(double deg);
    Vec3 lerp(const Vec3 &vec1, const Vec3 &vec2, const float t);
    float length(const Vec3 &vec);
    bool sameSign(const Vec3 &a, const Vec3 &b);
}