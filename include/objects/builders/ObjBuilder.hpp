/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjBuilder
*/

#ifndef EPITECH_RAYTRACER_OBJBUILDER_HPP
#define EPITECH_RAYTRACER_OBJBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Obj.hpp"
#include "scene/Scene.hpp"

class ObjBuilder: ObjectBuilder<Obj> {
    public:
        explicit ObjBuilder(Scene &scene);


    /**
     * @brief Build an object of type T.
     * @return UniquePointer to an object of type T.
     */
    std::unique_ptr<Obj> build(const libconfig::Setting &settings) override {
        bool paramExists;
        std::unique_ptr<Obj> obj = std::make_unique<Obj>(&_scene);

        for (auto &[argName, func]: _objSetters) {
            paramExists = settings.exists(argName);
            if (!paramExists && !func.hasDefaultValue)
                throw MissingParameterException(argName);
            if (!paramExists)
                continue;
            setParameter(*obj, argName, settings.lookup(argName));
        }
        return obj;
    }

    private:
        Scene &_scene;
};

#endif //EPITECH_RAYTRACER_OBJBUILDER_HPP
