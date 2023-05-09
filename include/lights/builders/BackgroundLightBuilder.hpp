/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** BackgroundLightBuilder
*/

#pragma once

#include "LightBuilder.hpp"
#include "lights/BackgroundLight.hpp"

class BackgroundLightBuilder : LightBuilder<BackgroundLight> {
    public:
        explicit BackgroundLightBuilder() {};
};
