/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

const Object *Scene::getClosest(const Ray *ray, const Object *ignore, bool ignoreLightSources) const
{
    Object *closest = nullptr;
    float dist = __FLT_MAX__;

    for (auto &obj : _pool) {
        if (obj == ignore || (ignoreLightSources && obj->getEmissionColor() != sf::Vector3f(0, 0, 0)
        && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
            continue;
        sf::Vector3f vec = obj->getIntersection(ray) - ray->getOrigin();
        float len = Math::length(vec);
        if (dist < len || !Math::sameSign(vec, ray->getDir()))
            continue;
        dist = len;
        closest = obj;
    }
    return closest;
}

const Object *Scene::getBetween(const Ray *ray, float dst, const Object *ignore, bool ignoreLightSources) const
{
    Object *closest = nullptr;
    float dist = __FLT_MAX__;

    for (auto &obj : _pool) {
        if (obj == ignore || (ignoreLightSources && obj->getEmissionColor() != sf::Vector3f(0, 0, 0)
        && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
            continue;
        sf::Vector3f vec = obj->getIntersection(ray) - ray->getOrigin();
        float len = Math::length(vec);
        if (dist < len || !Math::sameSign(vec, ray->getDir()) || len > dst)
            continue;
        dist = len;
        closest = obj;
    }
    return closest;
}