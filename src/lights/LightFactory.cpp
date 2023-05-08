/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightFactory
*/

#include "lights/LightFactory.hpp"
#include "lights/builders/DirectionalLightBuilder.hpp"
#include "lights/builders/LightPointBuilder.hpp"

LightFactory::LightFactory()
{
    this->_builders["directional"] =    std::make_shared<DirectionalLightBuilder>();
    this->_builders["point"] =          std::make_shared<LightPointBuilder>();
}
