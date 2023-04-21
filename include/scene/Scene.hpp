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
#include <memory>

class Scene {
public:
    bool _multithreadingEnabled = false;
    std::vector<std::string> _clusters;
    bool _preRenderEnabled = false;
    bool _continuousRenderEnabled = false;
    std::string _outputFile;
    bool _hotReloadEnabled = false;
    int _numberOfBounces = 0;
    int _raysPerPixel = 0;
    std::vector<std::shared_ptr<Object>> _objects;

    public:
        Scene() = default;
        ~Scene() {
            std::cout << "Multithreading enabled: " << std::boolalpha << _multithreadingEnabled << std::endl;
            std::cout << "Clusters: " << std::endl;
            for (auto &cluster : _clusters)
                std::cout << "\t" << cluster << std::endl;
            std::cout << "Pre-render enabled: " << std::boolalpha << _preRenderEnabled << std::endl;
            std::cout << "Continuous render enabled: " << std::boolalpha << _continuousRenderEnabled << std::endl;
            std::cout << "Output file: " << _outputFile << std::endl;
            std::cout << "Hot reload enabled: " << std::boolalpha << _hotReloadEnabled << std::endl;
            std::cout << "Number of bounces: " << _numberOfBounces << std::endl;
            std::cout << "Rays per pixel: " << _raysPerPixel << std::endl;
            std::cout << "Objects: " << std::endl;
            for (auto &obj : _objects)
                std::cout << "\t" << obj->getPos().x << ", " << obj->getPos().y << ", " << obj->getPos().z << std::endl;
        }

        // TODO: Implement these methods
        void setMultithreadingEnabled(const bool &enabled) {
            std::cout << "Setting multithreading enabled to " << std::boolalpha << enabled << std::endl;
            _multithreadingEnabled = enabled;
        };
        void setClusters(const std::vector<std::string> &clusters) {
            _clusters = clusters;
        };
        void setPreRenderEnabled(const bool &enabled) {
            std::cout << "Setting pre-render enabled to " << std::boolalpha << enabled << std::endl;
            _preRenderEnabled = enabled;
        };
        void setContinuousRenderEnabled(const bool &enabled) {
            std::cout << "Setting continuous render enabled to " << std::boolalpha << enabled << std::endl;
            _continuousRenderEnabled = enabled;
        };
        void setOutputFile(const std::string &file) {
            std::cout << "Setting output file to " << file << std::endl;
            _outputFile = file;
        };
        void setHotReloadEnabled(const bool &enabled) {
            std::cout << "Setting hot reload enabled to " << std::boolalpha << enabled << std::endl;
            _hotReloadEnabled = enabled;
        };
        void setNumberOfBounces(const int &bounces) {
            std::cout << "Setting number of bounces to " << bounces << std::endl;
            _numberOfBounces = bounces;
        };
        void setRaysPerPixel(const int &rays) {
            std::cout << "Setting rays per pixel to " << rays << std::endl;
            _raysPerPixel = rays;
        };
        void setCamera(const int &camera) {
//            _camera = camera;
        };
        void setObjects(const std::vector<std::shared_ptr<Object>> &objects) {
            _objects = objects;
        };
        void setLights(const std::vector<lightPoint> &lights) {};

        void addObject(Object *obj) {_pool.push_back(obj);};
        void addLightPoint(lightPoint light) {_lightsPoints.push_back(light);};
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
        std::vector<lightPoint> getLightPoints() const {return _lightsPoints;};
        Object *getBetween(Ray *ray, float dst, Object *ignore = nullptr, bool ignoreLightSources = false) const {
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

    protected:
    private:
        std::vector<Object *> _pool;
        std::vector<lightPoint> _lightsPoints;
};
