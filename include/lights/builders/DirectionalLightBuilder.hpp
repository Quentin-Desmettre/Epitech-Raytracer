/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** DirectionalLightBuilder
*/

#pragma once

#include "LightBuilder.hpp"
#include "lights/DirectionalLight.hpp"

class DirectionalLightBuilder : LightBuilder<DirectionalLight> {
    public:
        explicit DirectionalLightBuilder();
};
