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
#include <fstream>

typedef libconfig::Setting::Type Type;

SceneBuilder::SceneBuilder(int ac, char **av)
{
    if (ac != 2)
        throw InvalidArgumentsException("Usage: ./raytracer <config_file>");
    _file = av[1];
    _config.readFile(av[1]);
    _settings = &_config.getRoot();
    setSetters();
}

SceneBuilder::SceneBuilder(const std::string &path)
{
    _config.readFile(path.c_str());
    _settings = &_config.getRoot();
    setSetters();
}

void SceneBuilder::setSetters()
{
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
    std::unique_ptr<Scene> scene = ABuilder<Scene>::build(*_settings);

    std::ifstream file(_file);
    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    scene->setRawConfiguration(str);
    file.close();
    return scene;
}

void SceneBuilder::setCamera(Scene &scene, const std::string &param,
                                           const libconfig::Setting &setting)
{
    sf::Vector2u resolution = {
            static_cast<unsigned int>(setting["resolution"]["x"]),
            static_cast<unsigned int>(setting["resolution"]["y"])
    };
    sf::Vector3f position = {
            static_cast<float>(setting["position"]["x"]),
            static_cast<float>(setting["position"]["y"]),
            static_cast<float>(setting["position"]["z"])
    };
    auto cam = std::make_shared<Camera>(position, sf::Vector3f{0, 0, 1}, resolution);
    cam->setRot({0, 0.25, 0});
    setParameter(scene, param, cam);
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
