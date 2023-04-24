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
#include <utility>
#include <vector>
#include <memory>

class Camera {
public:
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    Camera(sf::Vector3f pos = sf::Vector3f(0, 0, -2.0f), sf::Vector3f rot = sf::Vector3f(0, 0, 1), sf::Vector2u size = sf::Vector2u(800, 800)):
            _pos(pos), _rot(rot), _size(size) {};
    ~Camera() = default;
    void setPos(sf::Vector3f pos) {_pos = pos;};
    void setRot(sf::Vector3f rot) {_rot = rot;};
    sf::Vector3f getPos() const {return _pos;};
    sf::Vector3f getRot() const {return _rot;};
    sf::Vector2u getResolution() const {return _size;};
    void move(Direction dir, float speed);
    void turn(float x, float y);

protected:
private:
    sf::Vector3f _pos;
    sf::Vector3f _rot;
    sf::Vector2u _size;
};

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
    sf::VertexArray _vertexArray;

    public:
        Scene() = default;
        ~Scene() = default;

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
        void setCamera(const std::shared_ptr<Camera> &camera) {
            _camera = camera;
        };
        sf::VertexArray &getVertexArray() { return _vertexArray;}
        void setObjects(const std::vector<std::shared_ptr<Object>> &objects) {
            _pool = objects;
        };
        void setLights(const std::vector<lightPoint> &lights) {};
        void setRawConfiguration(const std::string &raw) {
            _rawConfig = raw;
        };
        const Camera &getCamera() const {
            return *_camera;
        };

        std::string getRawConfiguration() const {
            return _rawConfig;
        };
        int getRaysPerPixel() const {
            return _raysPerPixel;
        };
        int getNbBounces() const {
            return _numberOfBounces;
        };

        // TODO
        sf::Vector2u getResolution() const {return _camera->getResolution();}
        void addLightPoint(const lightPoint& light) {_lightsPoints.push_back(light);};
        auto getPool() const {return _pool;};
        Object *getClosest(const Ray *ray, const Object *ignore = nullptr, bool ignoreLightSources = false) const;
        std::vector<lightPoint> getLightPoints() const {return _lightsPoints;};
        Object *getBetween(Ray *ray, float dst, Object *ignore = nullptr, bool ignoreLightSources = false) const {
            Object *closest = nullptr;
            float dist = __FLT_MAX__;

            for (auto &obj : _pool) {
                if (obj.get() == ignore || (ignoreLightSources && obj->getEmissionColor() != sf::Vector3f(0, 0, 0)
                                      && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
                    continue;
                sf::Vector3f vec = obj->getIntersection(ray) - ray->getOrigin();
                float len = Math::length(vec);
                if (dist < len || !Math::sameSign(vec, ray->getDir()) || len > dst)
                    continue;
                dist = len;
                closest = obj.get();
            }
            return closest;
        };

    protected:
    private:
        std::vector<std::shared_ptr<Object>> _pool;
        std::vector<lightPoint> _lightsPoints;
        std::string _rawConfig;
        std::shared_ptr<Camera> _camera;
};
