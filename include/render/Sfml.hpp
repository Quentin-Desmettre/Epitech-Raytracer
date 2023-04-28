/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SFML
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

typedef sf::Glsl::Vec3 Vec3;

#define unused __attribute_maybe_unused__

#define VEC3_ZERO Vec3(0, 0, 0)

#define WHITE Vec3(1, 1, 1)
#define RED Vec3(1, 0, 0)
#define GREEN Vec3(0, 1, 0)
#define BLUE Vec3(0, 0, 1)
#define YELLOW Vec3(1, 1, 0)
#define MAGENTA Vec3(1, 0, 1)
#define CYAN Vec3(0, 1, 1)

#define INF __FLT_MAX__

inline Vec3 operator*(Vec3 vec, Vec3 vec2) {
    return Vec3(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z);
}

inline void operator*=(Vec3 &vec, Vec3 vec2) {
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
}

inline Vec3 operator/(Vec3 vec, size_t num) {
    return Vec3(vec.x / num, vec.y / num, vec.z / num);
}
