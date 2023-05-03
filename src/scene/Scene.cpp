/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Scene
*/

#include "scene/Scene.hpp"

void Scene::setMultithreadingEnabled(const bool &enabled)
{
    _multithreadingEnabled = enabled;
}

void Scene::setClusters(const std::vector<std::string> &clusters)
{
    _clusters = clusters;
}

void Scene::setPreRenderEnabled(const bool &enabled)
{
    _preRenderEnabled = enabled;
}

void Scene::setContinuousRenderEnabled(const bool &enabled)
{
    _continuousRenderEnabled = enabled;
}

void Scene::setOutputFile(const std::string &file)
{
    _outputFile = file;
}

void Scene::setHotReloadEnabled(const bool &enabled)
{
    _hotReloadEnabled = enabled;
}

void Scene::setNumberOfBounces(const int &bounces)
{
    _numberOfBounces = bounces;
}

void Scene::setRaysPerPixel(const int &rays)
{
    _raysPerPixel = rays;
}

void Scene::setCamera(const std::shared_ptr<Camera> &camera)
{
    _camera = camera;
}

void Scene::setObjects(const std::vector<std::shared_ptr<IObject>> &objects)
{
    _pool = objects;
}

void Scene::setLights(const std::vector<LightPoint> &lights)
{
    _lightsPoints = lights;
}

void Scene::setRawConfiguration(const std::string &raw)
{
    _rawConfig = raw;
}

//======================//
//        GETTERS       //
//======================//
bool Scene::isMultithreadingEnabled() const
{
    return _multithreadingEnabled;
}

const std::vector<std::string> &Scene::getClusters() const
{
    return _clusters;
}

bool Scene::isPreRenderEnabled() const
{
    return _preRenderEnabled;
}

bool Scene::isContinuousRenderEnabled() const
{
    return _continuousRenderEnabled;
}

const std::string &Scene::getOutputFile() const
{
    return _outputFile;
}

bool Scene::isHotReloadEnabled() const
{
    return _hotReloadEnabled;
}

const Camera &Scene::getCamera() const
{
    return *_camera;
}

Camera &Scene::getCamera()
{
    return *_camera;
}

std::string Scene::getRawConfiguration() const
{
    return _rawConfig;
}

int Scene::getRaysPerPixel() const
{
    return _raysPerPixel;
}

int Scene::getNbBounces() const
{
    return _numberOfBounces;
}

sf::Vector2u Scene::getResolution() const
{
    return _camera->getResolution();
}

float Scene::getAntiAliasing() const
{
    return _camera->getAntiAliasing();
}

const IObject *Scene::getClosest(const Ray &ray, const IObject *ignore, bool ignoreLightSources) const
{
    IObject *closest = nullptr;
    float dist = INF;

    for (const auto &obj : _pool) {
        if (obj.get() == ignore || (ignoreLightSources && obj->getEmissionColor() != VEC3_ZERO
        && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
            continue;
        Vec3 vec = obj->getIntersection(ray) - ray.getOrigin();
        float len = Math::length(vec);
        if (dist < len || !Math::sameSign(vec, ray.getDir()))
            continue;
        dist = len;
        closest = obj.get();
    }
    return closest;
}

const IObject *Scene::getBetween(const Ray &ray, float dst, const IObject *ignore, bool ignoreLightSources) const
{
    IObject *closest = nullptr;
    float dist = INF;

    for (auto &obj : _pool) {
        if (obj.get() == ignore || (ignoreLightSources && obj->getEmissionColor() != VEC3_ZERO
        && obj->getEmissionIntensity() > 0) || !obj->intersect(ray))
            continue;
        Vec3 vec = obj->getIntersection(ray) - ray.getOrigin();
        float len = Math::length(vec);
        if (dist < len || !Math::sameSign(vec, ray.getDir()) || len > dst)
            continue;
        if (obj->getTransparency() && Math::randomf(0, 1) > obj->getRoughness())
            continue;
        dist = len;
        closest = obj.get();
    }
    return closest;
}

std::vector<std::shared_ptr<IObject>> Scene::getPool() const
{
    return _pool;
}

std::vector<LightPoint> Scene::getLightPoints() const
{
    return _lightsPoints;
}

//======================//
//        METHODS       //
//======================//
void Scene::addLightPoint(const LightPoint& light)
{
    _lightsPoints.push_back(light);
}

void Scene::addObject(std::unique_ptr<IObject> &&object)
{
    _pool.push_back(std::move(object));
}
