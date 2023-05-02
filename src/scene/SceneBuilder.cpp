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
#include "network/TcpSocket.hpp"

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
    // Resolve imports, by reading the file and replacing the imports with the file content
    libconfig::Config imports; imports.readFile(path.c_str());
    libconfig::Setting &importsSettings = imports.getRoot();
    if (importsSettings.exists("imports")) {
        // Fetch imports, and put them in a temporary file
        std::string tmpFile = "/tmp/raytracer_config_" + std::to_string(Math::random(0, 1000000)) + ".cfg";
        std::ofstream tmp(tmpFile);
        if (!tmp.is_open())
            throw InvalidArgumentsException("Could not open temporary file: " + tmpFile);
        for (int i = 0; i < importsSettings["imports"].getLength(); i++)
            tmp << getFileContent(importsSettings["imports"][i]);
        tmp << getFileContent(path);
        _file = tmpFile;
    } else
        _file = path;
    _config.readFile(_file.c_str());
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

    scene->getCamera().updateRayDirs();
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
    std::cout << "Setting camera" << std::endl;
    if (!setting.exists("resolution"))      throw InvalidParameterValueException("Missing resolution for camera");
    if (!setting.exists("position"))        throw InvalidParameterValueException("Missing position for camera");
    if (!setting.exists("antiAliasing"))    throw InvalidParameterValueException("Missing antiAliasing for camera");
    if (!setting.exists("rotation"))        throw InvalidParameterValueException("Missing rotation for camera");

    // Fetch resolution
    sf::Vector2u resolution = {
            static_cast<unsigned int>(setting["resolution"]["x"]),
            static_cast<unsigned int>(setting["resolution"]["y"])
    };
    if (resolution.x <= 0 || resolution.y <= 0)
        throw InvalidParameterValueException("Invalid resolution for camera");

    // Fetch position and rotation
    sf::Vector3f position = {
            getFloat(setting["position"]["x"]),
            getFloat(setting["position"]["y"]),
            getFloat(setting["position"]["z"])
    };
    sf::Vector3f rot = {
            getFloat(setting["rotation"]["x"]),
            getFloat(setting["rotation"]["y"]),
            getFloat(setting["rotation"]["z"])
    };

    // Fetch antiAliasing
    float antiAliasing = getFloat(setting["antiAliasing"]);
    if (antiAliasing <= 0 || !Math::isPowerOfTwo(antiAliasing))
        throw InvalidParameterValueException("Invalid antiAliasing");

    // Fetch fov
    float fov = setting.exists("fieldOfView") ? getFloat(setting["fieldOfView"]) : 90;
    if (fov <= 0 || fov > 180)
        throw InvalidParameterValueException("Invalid fieldOfView");

    // Build camera
    auto cam = std::make_shared<Camera>(position, rot, resolution);
    cam->setAntiAliasing(antiAliasing);
    cam->setFov(fov);
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
        // Check ip:port
        if (!Network::isIpPortValid(ip))
            throw InvalidParameterValueException("Invalid ip address for cluster: " + ip);
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

void SceneBuilder::setLights(unused Scene &scene, unused const std::string &param,
unused const libconfig::Setting &setting)
{
}

std::string SceneBuilder::getFileContent(const std::string &path)
{
    std::ifstream file(path);

    if (!file)
        throw InvalidArgumentsException("Could not open file: " + path);
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    return content;
}
