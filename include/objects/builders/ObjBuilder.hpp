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

class ObjBuilder: ObjectBuilder<Obj> {
    public:
        explicit ObjBuilder() {}
};

#endif //EPITECH_RAYTRACER_OBJBUILDER_HPP
