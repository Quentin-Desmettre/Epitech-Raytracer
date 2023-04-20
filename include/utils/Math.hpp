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
    Vec3 normalize(Vec3 vec);
    float dot(Vec3 vec1, Vec3 vec2);
    float random(float min, float max);
    float randomNormDistrib();
    Vec3 randomDir();
    float sign(float val);
    Vec3 cross(Vec3 vec1, Vec3 vec2);
    double toRad(double deg);
    Vec3 lerp(Vec3 vec1, Vec3 vec2, float t);
    float length(Vec3 vec);
    bool sameSign(Vec3 a, Vec3 b);
    Vec3 rotate(Vec3 vec, Vec3 axis, float angle);
    Mat4 lookAt(Vec3 eye, Vec3 center, Vec3 up);
    Mat4 perspective(float radFov, float x, float y, float near, float far);
}
