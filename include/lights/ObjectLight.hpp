/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectLight
*/

#pragma once

#include "ILight.hpp"

class ObjectLight : public ALight {
    public:
        ObjectLight() = default;
        ~ObjectLight() = default;
        Vec3 illuminate(const Vec3 &normal, const Vec3 &rayColor, const Vec3 &rayDir) const override;
    protected:
    private:
};
