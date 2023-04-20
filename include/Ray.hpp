/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Ray
*/

#pragma once

#include "utils/Math.hpp"
#include <SFML/Graphics.hpp>

class Ray {
    public:
        Ray(Vec3 origin = Vec3(0, 0, 0), Vec3 dir = Vec3(0, 0, 1)) :
        _origin(origin), _dir(dir) {};
        ~Ray() = default;

        // Setters
        void setOrigin(Vec3 origin) {_origin = origin;};
        void setDir(Vec3 dir) {_dir = dir;};

        // Getters
        Vec3 getOrigin() const {return _origin;};
        Vec3 getDir() const {return _dir;};

        // Methods
        void reflect(Vec3 normal, float reflectivity) {
            Vec3 tmp = Math::randomDir();
            Vec3 specular = _dir - 2.0f * Math::dot(_dir, normal) * normal;
            Vec3 diffuse = tmp * Math::sign(Math::dot(normal, tmp));
            _dir = specular * reflectivity + diffuse * (1.0f - reflectivity);
        };
    protected:
    private:
        Vec3 _origin;
        Vec3 _dir;
};
