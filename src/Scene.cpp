/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

const AObject *Scene::getClosest(const Ray &ray, const AObject *ignore, bool ignoreLightSources) const
{
    AObject *closest = nullptr;
    float dist = INF;

    for (const auto &obj : _pool) {
        if (obj == ignore || (ignoreLightSources && obj->getEmissionColor() != Vec3(0, 0, 0)
        && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
            continue;
        Vec3 vec = obj->getIntersection(ray) - ray.getOrigin();
        float len = Math::length(vec);
        if (dist < len || !Math::sameSign(vec, ray.getDir()))
            continue;
        dist = len;
        closest = obj;
    }
    return closest;
}

const AObject *Scene::getBetween(const Ray &ray, float dst, const AObject *ignore, bool ignoreLightSources) const
{
    AObject *closest = nullptr;
    float dist = INF;

    for (auto &obj : _pool) {
        if (obj == ignore || (ignoreLightSources && obj->getEmissionColor() != Vec3(0, 0, 0)
        && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
            continue;
        Vec3 vec = obj->getIntersection(ray) - ray.getOrigin();
        float len = Math::length(vec);
        if (dist < len || !Math::sameSign(vec, ray.getDir()) || len > dst)
            continue;
        dist = len;
        closest = obj;
    }
    return closest;
}