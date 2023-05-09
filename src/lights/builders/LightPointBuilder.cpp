/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPointBuilder
*/

#include "lights/builders/LightPointBuilder.hpp"

LightPointBuilder::LightPointBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    _objSetters.push_back({"position", {Type::TypeGroup, reinterpret_cast<LightSetterFunc>(&LightPoint::setPos), true}});
    _objGroupSetters.push_back({"position", static_cast<BuilderSetterFunc>(&LightPointBuilder::setPosition)});
#pragma GCC diagnostic pop
}
