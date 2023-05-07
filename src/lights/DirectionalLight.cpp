/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** DirectionalLight
*/

#include "scene/Scene.hpp"
#include "render/Ray.hpp"
#include "lights/DirectionalLight.hpp"

DirectionalLight::DirectionalLight(Vec3 dir, Vec3 color) {
    _dir = Math::normalize(dir);
    _color = color;
};

Vec3 DirectionalLight::illuminate(const Vec3 &normal, const Vec3 &inter, const Vec3 &color,
const Scene &pool, const IObject *obj) const
{
    const Ray ray(inter, -_dir);

    // returns if there is an object between the sun and the intersection
    if (pool.getBetween(ray, 1, obj, true) != nullptr)
        return VEC3_ZERO;
    // returns if the sun is not visible from the intersection
    // if (Math::dot(normal, ray.getDir()) <= 0)
    //     return VEC3_ZERO;
    Vec3 result = std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * _color;
    if (obj->isReflective() || obj->isTransparent())
        result *= obj->getRoughness();
    return result;
}
