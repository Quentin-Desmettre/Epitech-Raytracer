/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPoint
*/

#include "scene/Scene.hpp"
#include "render/Ray.hpp"
#include "lights/LightPoint.hpp"

LightPoint::LightPoint(Vec3 pos, Vec3 color, float intensity)
{
    _pos = pos;
    _color = color;
    _intensity = intensity;
}

Vec3 LightPoint::illuminate(const Vec3 &normal, const Vec3 &inter, const Vec3 &color,
const Scene &pool, const IObject *obj) const
{
    Ray ray(inter, Math::normalize(_pos - inter));
    Vec3 result = VEC3_ZERO;

    // adding light of light points if there is no object between the intersection and the light point
    if (pool.getBetween(ray, Math::length(_pos - inter), obj, true) == nullptr) {
        result = std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * _color;
        if (obj->isReflective() || obj->isTransparent())
            result *= obj->getRoughness();
    }
    return result;
}
