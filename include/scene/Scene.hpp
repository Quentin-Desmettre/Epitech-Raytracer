/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#pragma once

#include "render/Ray.hpp"
#include "objects/Object.hpp"
#include "lights/LightPoint.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "render/Camera.hpp"

class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        // Setters
        void setMultithreadingEnabled(const bool &enabled);
        void setClusters(const std::vector<std::string> &clusters);
        void setPreRenderEnabled(const bool &enabled);
        void setContinuousRenderEnabled(const bool &enabled);
        void setOutputFile(const std::string &file);
        void setHotReloadEnabled(const bool &enabled);
        void setNumberOfBounces(const int &bounces);
        void setRaysPerPixel(const int &rays);
        void setCamera(const std::shared_ptr<Camera> &camera);
        void addObjects(const std::vector<std::shared_ptr<IObject>> &objects);
        void setLights(const std::vector<LightPoint> &lights);
        void setRawConfiguration(const std::string &raw);

        void test() const {std::cout << _pool.size() << std::endl;}
        // Getters
        bool isMultithreadingEnabled() const;
        const std::vector<std::string> &getClusters() const;
        bool isPreRenderEnabled() const;
        bool isContinuousRenderEnabled() const;
        const std::string &getOutputFile() const;
        bool isHotReloadEnabled() const;
        int getNbBounces() const;
        int getRaysPerPixel() const;
        const Camera &getCamera() const;
        Camera &getCamera();
        std::vector<std::shared_ptr<IObject>> getPool() const;
        std::vector<LightPoint> getLightPoints() const;
        std::string getRawConfiguration() const;
        sf::Vector2u getResolution() const;
        float getAntiAliasing() const;
        const IObject *getClosest(const Ray &ray, const IObject *ignore = nullptr, bool ignoreLightSources = false) const;
        const IObject *getBetween(const Ray &ray, float dst, const IObject *ignore = nullptr, bool ignoreLightSources = false) const;

        // Methods
        void addLightPoint(const LightPoint& light);
        void addObject(std::unique_ptr<IObject> &&object);

    protected:
    private:
        std::vector<std::shared_ptr<IObject>> _pool;
        std::vector<LightPoint> _lightsPoints;
        std::string _rawConfig;
        std::shared_ptr<Camera> _camera;
        bool _multithreadingEnabled = false;
        std::vector<std::string> _clusters;
        bool _preRenderEnabled = false;
        bool _continuousRenderEnabled = false;
        std::string _outputFile;
        bool _hotReloadEnabled = false;
        int _numberOfBounces = 0;
        int _raysPerPixel = 0;
};
