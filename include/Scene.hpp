/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#pragma once

#include "Ray.hpp"
#include "objects/Object.hpp"
#include <iostream>
#include <vector>

class Scene {
    public:
        Scene() = default;
        ~Scene() = default;
        void addObject(Object *obj) {_pool.push_back(obj);};
        std::vector<Object *> getPool() {return _pool;};
        Object *getClosest(const Ray *ray, const Object *ignore = nullptr, bool ignoreLightSources = false) const {
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
        };
    protected:
    private:
        std::vector<Object *> _pool;
};
