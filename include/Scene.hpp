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
        void addObject(AObject *obj) {_pool.push_back(obj);};
        void addLightPoint(LightPoint light) {_lightsPoints.push_back(light);};
        void clear() {_pool.clear(); _lightsPoints.clear();};

        // Getters
        const std::vector<AObject *> &getPool() const {return _pool;};
        const std::vector<LightPoint> &getLightPoints() const {return _lightsPoints;};
        const AObject *getClosest(const Ray &ray, const AObject *ignore = nullptr, bool ignoreLightSources = false) const;
        const AObject *getBetween(const Ray &ray, float dst, const AObject *ignore = nullptr, bool ignoreLightSources = false) const;
    protected:
    private:
        std::vector<AObject *> _pool;
        std::vector<LightPoint> _lightsPoints;
};
