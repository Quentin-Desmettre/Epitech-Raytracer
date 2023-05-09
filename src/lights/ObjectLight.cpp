/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectLight
*/

#include "lights/ObjectLight.hpp"

Vec3 ObjectLight::illuminate(const Vec3 &normal, const Vec3 &rayColor, const Vec3 &rayDir) const
{
    float hitAngle = std::max(Math::dot(normal, -rayDir), 0.0f);
    return _color * rayColor * hitAngle * _intensity;
}
