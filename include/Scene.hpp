/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#pragma once

#include "Ray.hpp"
#include "objects/Object.hpp"
#include "LightPoint.hpp"
#include <vector>

class Scene {
    public:
        Scene() {
            _pool.reserve(100);
            _lightsPoints.reserve(100);
        };
        ~Scene() = default;

        // Setters
        void addObject(Object *obj) {_pool.push_back(obj);};
        void addLightPoint(LightPoint light) {_lightsPoints.push_back(light);};
        void clear() {_pool.clear(); _lightsPoints.clear();};

        // Getters
        const std::vector<Object *> &getPool() const {return _pool;};
        const std::vector<LightPoint> &getLightPoints() const {return _lightsPoints;};
        const Object *getClosest(const Ray &ray, const Object *ignore = nullptr, bool ignoreLightSources = false) const;
        const Object *getBetween(const Ray &ray, float dst, const Object *ignore = nullptr, bool ignoreLightSources = false) const;
    protected:
    private:
        std::vector<Object *> _pool;
        std::vector<LightPoint> _lightsPoints;
};
