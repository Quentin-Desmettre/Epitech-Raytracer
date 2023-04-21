/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SceneBuilder
*/

#include <memory>
#include <regex>
#include "scene/SceneBuilder.hpp"
#include "Exceptions.hpp"
#include "objects/ObjectFactory.hpp"

typedef libconfig::Setting::Type Type;

SceneBuilder::SceneBuilder(int ac, char **av)
{
    if (ac != 2)
        throw InvalidArgumentsException("Usage: ./raytracer <config_file>");
    _config.readFile(av[1]);
    _settings = &_config.getRoot();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    _objSetters = {
            {"multithreading",      {Type::TypeBoolean, reinterpret_cast<SetterFunc>(&Scene::setMultithreadingEnabled),     true}},
            {"clusters",            {Type::TypeList,    reinterpret_cast<SetterFunc>(&Scene::setClusters),                  true}},
            {"camera",              {Type::TypeGroup,   reinterpret_cast<SetterFunc>(&Scene::setCamera),                    true}},
            {"pre-render",          {Type::TypeBoolean, reinterpret_cast<SetterFunc>(&Scene::setPreRenderEnabled),          true}},
            {"continuous-render",   {Type::TypeBoolean, reinterpret_cast<SetterFunc>(&Scene::setContinuousRenderEnabled),   true}},
            {"output",              {Type::TypeString,  reinterpret_cast<SetterFunc>(&Scene::setOutputFile),                true}},
            {"hot-reload",          {Type::TypeBoolean, reinterpret_cast<SetterFunc>(&Scene::setHotReloadEnabled),          true}},
            {"number-of-bounces",   {Type::TypeInt,     reinterpret_cast<SetterFunc>(&Scene::setNumberOfBounces),           true}},
            {"rays-per-pixel",      {Type::TypeInt,     reinterpret_cast<SetterFunc>(&Scene::setRaysPerPixel),              true}},
            {"objects",             {Type::TypeList,    reinterpret_cast<SetterFunc>(&Scene::setObjects),                   true}},
            {"lights",              {Type::TypeList,    reinterpret_cast<SetterFunc>(&Scene::setLights),                    true}}
    };

    _objListSetters = {
            {"objects",     static_cast<BuilderSetterFunc>(&SceneBuilder::setObjects)},
            {"lights",      static_cast<BuilderSetterFunc>(&SceneBuilder::setLights)},
            {"clusters",    static_cast<BuilderSetterFunc>(&SceneBuilder::setClusters)}
    };

    _objGroupSetters = {
            {"camera",  static_cast<BuilderSetterFunc>(&SceneBuilder::setCamera)}
    };
#pragma GCC diagnostic pop

}

std::unique_ptr<Scene> SceneBuilder::build()
{
    return ABuilder<Scene>::build(*_settings);
}

void SceneBuilder::setCamera(Scene &scene, const std::string &param,
                                           const libconfig::Setting &setting)
{
//    SharedCamera cam = CameraBuilder(setting).buildCamera();
//
//    setParameter<SharedCamera>(setting, cam);
}

void SceneBuilder::setClusters(Scene &scene, const std::string &param,
                                             const libconfig::Setting &setting)
{
    std::vector<std::string> clustersIps;

    for (int i = 0; i < setting.getLength(); i++) {
        if (setting[i].getType() != libconfig::Setting::TypeString)
            throw InvalidParameterValueException("Invalid type for clusters");

        std::string ip = setting[i];
        // Check ip:port address regex
        // Trust me, this regex works

//        if (!Network::isIpValid(ip))
//            throw InvalidParameterValueException("Invalid ip address for cluster: " + ip);
        clustersIps.push_back(setting[i]);
    }
    setParameter(scene, param, clustersIps);
}

void SceneBuilder::setObjects(Scene &scene, const std::string &param,
                                            const libconfig::Setting &setting)
{
    ObjectFactory objectFactory;

    setGroupList(scene, param, setting, &objectFactory);
}

void SceneBuilder::setLights(Scene &scene, const std::string &param,
                                           const libconfig::Setting &setting)
{
}
