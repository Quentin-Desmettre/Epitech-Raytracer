/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** BackgroundLight
*/

#pragma once

#include "render/Sfml.hpp"
#include "ILight.hpp"

class BackgroundLight : public ALight {
    public:
        BackgroundLight(Vec3 color = WHITE, float intensity = 1.0f) : ALight(color, intensity) {};
        ~BackgroundLight() = default;
};
