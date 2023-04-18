/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#pragma once

#include "Ray.hpp"
#include "objects/Object.hpp"
#include "lightPoint.hpp"
#include <iostream>
#include <vector>

class Scene {
    public:
        Scene() = default;
        ~Scene() = default;
        void addObject(Object *obj) {_pool.push_back(obj);};
        void addLightPoint(lightPoint light) {_lightsPoints.push_back(light);};
        std::vector<Object *> getPool() {return _pool;};
        Object *getClosest(Ray *ray, Object *ignore = nullptr, bool ignoreLightSources = false) {
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
        std::vector<lightPoint> _lightsPoints;
        Object *getBetween(Ray *ray, float dst, Object *ignore = nullptr, bool ignoreLightSources = false) {
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
        };
        std::vector<lightPoint> getLightPoints() {return _lightsPoints;};
};
