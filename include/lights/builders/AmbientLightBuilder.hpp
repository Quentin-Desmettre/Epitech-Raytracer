/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** AmbientLightBuilder
*/

#pragma once

#include "LightBuilder.hpp"
#include "lights/ILight.hpp"

class AmbientLightBuilder : LightBuilder<ALight> {
    public:
        explicit AmbientLightBuilder() {};
};
