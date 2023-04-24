/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SceneBuilder
*/

#ifndef EPITECH_RAYTRACER_SCENEBUILDER_HPP
#define EPITECH_RAYTRACER_SCENEBUILDER_HPP

#include "Scene.hpp"
#include "libconfig.h++"
#include "Exceptions.hpp"
#include <memory>
#include "IFactory.hpp"
#include "ABuilder.hpp"

class SceneBuilder: public ABuilder<Scene> {
public:
    SceneBuilder(int ac, char **av);
    explicit SceneBuilder(const std::string &path);
    ~SceneBuilder() override = default;

    std::unique_ptr<Scene> build();

private:
    std::string _file;

    // Constructor utility
    void setSetters();

    libconfig::Config _config;
    libconfig::Setting *_settings;

    // Group methods
    void setCamera(Scene &scene, const std::string &param, const libconfig::Setting &setting);

    // List methods
    void setLights(Scene &scene, const std::string &param, const libconfig::Setting &setting);
    void setObjects(Scene &scene, const std::string &param, const libconfig::Setting &setting);
    void setClusters(Scene &scene, const std::string &param, const libconfig::Setting &setting);

};

#endif //EPITECH_RAYTRACER_SCENEBUILDER_HPP
