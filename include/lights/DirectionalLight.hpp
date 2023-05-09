/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** DirectionalLight
*/

#pragma once

#include "ILight.hpp"

class DirectionalLight : public ALight {
    public:
        DirectionalLight(Vec3 dir = Vec3(-1, 1, 0), Vec3 color = Vec3(1, 1, 1));
        ~DirectionalLight() = default;

        Vec3 getDir() {return _dir;};
        void setDir(const Vec3 &dir) {_dir = Math::normalize(dir);};
        Vec3 illuminate(const Vec3 &normal, const Vec3 &inter, const Vec3 &color, const Scene &pool, const IObject *obj) const;
    protected:
    private:
        Vec3 _dir;
};
