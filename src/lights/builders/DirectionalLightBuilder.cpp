/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** DirectionalLightBuilder
*/

#include "lights/builders/DirectionalLightBuilder.hpp"

DirectionalLightBuilder::DirectionalLightBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    _objSetters.push_back({"direction", {Type::TypeGroup, reinterpret_cast<LightSetterFunc>(&DirectionalLight::setDir), true}});
    _objGroupSetters.push_back({"direction", static_cast<BuilderSetterFunc>(&DirectionalLightBuilder::setPosition)});
#pragma GCC diagnostic pop
}
