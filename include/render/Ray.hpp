/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Ray
*/

#pragma once

#include "utils/Math.hpp"
#include "objects/Object.hpp"
#include <SFML/Graphics.hpp>

class Ray {
    public:
        Ray(Vec3 origin = Vec3(0, 0, 0), Vec3 dir = Vec3(0, 0, 1), Vec3 color = Vec3(1, 1, 1)) :
        _origin(origin), _dir(dir), _color(color) {};
        ~Ray() = default;

        // Setters
        void setOrigin(Vec3 origin) {_origin = origin;};
        void setDir(Vec3 dir) {_dir = dir;};
        void setColor(Vec3 color) {_color = color;};

        // Getters
        Vec3 getOrigin() const {return _origin;};
        Vec3 getDir() const {return _dir;};
        Vec3 getColor() const {return _color;};

        // Methods
        void reflect(Vec3 normal, const IObject *obj);
    protected:
    private:
        Vec3 _origin;
        Vec3 _dir;
        Vec3 _color;
};
