/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ILight
*/

#pragma once

#include "render/Sfml.hpp"
#include "../utils/Math.hpp"
#include "scene/Scene.hpp"

class ILight {
    public:
        ~ILight() = default;
        virtual Vec3 illuminate(Vec3 normal, Vec3 inter, Vec3 color,
        const Scene *pool, const AObject *obj) const = 0;
    protected:
    private:
};
