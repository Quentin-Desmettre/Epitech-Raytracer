/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPointBuilder
*/

#pragma once

#include "LightBuilder.hpp"
#include "lights/LightPoint.hpp"

class LightPointBuilder : LightBuilder<LightPoint> {
    public:
        explicit LightPointBuilder();
};
