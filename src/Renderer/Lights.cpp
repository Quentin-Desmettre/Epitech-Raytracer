/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

Vec3 Renderer::addSunLight(Vec3 normal, Vec3 inter,
Vec3 color, const Scene *pool, const Object *obj) const
{
    static float length = Math::length(_sunLight);
    const Ray ray(inter, -_sunLight);

    // returns if there is an object between the sun and the intersection
    if (pool->getBetween(ray, length, obj, true) != nullptr)
        return VEC3_ZERO;
    // returns if the sun is not visible from the intersection
    // if (Math::dot(normal, ray.getDir()) <= 0)
    //     return VEC3_ZERO;
    return std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * _sunColor;
}

Vec3 Renderer::addLightOfPoints(Vec3 normal, Vec3 inter,
Vec3 color, const Scene *pool, const Object *obj) const
{
    Vec3 light = VEC3_ZERO;

    for (auto &LightPoint : pool->getLightPoints()) {
        Ray ray(inter, Math::normalize(LightPoint.getPos() - inter));
        // adding light of light points if there is no object between the intersection and the light point
        if (pool->getBetween(ray, Math::length(LightPoint.getPos() - inter), obj, true) == nullptr) {
            Vec3 tmp = std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * LightPoint.getColorF();
            light += tmp;
        }
    }
    return light;
}
