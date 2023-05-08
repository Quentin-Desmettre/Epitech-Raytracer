/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightFactory
*/

#include "lights/LightFactory.hpp"
#include "lights/builders/DirectionalLightBuilder.hpp"
#include "lights/builders/LightPointBuilder.hpp"
#include "lights/builders/BackgroundLightBuilder.hpp"
#include "lights/builders/AmbientLightBuilder.hpp"

LightFactory::LightFactory()
{
    this->_builders["directional"] =    std::make_shared<DirectionalLightBuilder>();
    this->_builders["point"] =          std::make_shared<LightPointBuilder>();
    this->_builders["background"] =     std::make_shared<BackgroundLightBuilder>();
    this->_builders["ambient"] =        std::make_shared<AmbientLightBuilder>();
}
