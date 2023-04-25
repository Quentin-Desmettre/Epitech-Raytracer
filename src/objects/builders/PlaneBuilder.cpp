/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PlaneBuilder
*/

#include "objects/builders/PlaneBuilder.hpp"

typedef libconfig::Setting::Type Type;

PlaneBuilder::PlaneBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    // Axis setter must be called before position setter
    _objSetters.push_back({"axis", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Plane::setAxis), false}});

    // New position setter
    _objSetters.erase(_objSetters.begin() + static_cast<int>(indexOf("position", _objSetters)));
    _objSetters.push_back({"position", {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Plane::setPosition), false}});
#pragma GCC diagnostic pop
}
