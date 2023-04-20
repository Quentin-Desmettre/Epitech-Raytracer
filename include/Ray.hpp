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
        Ray(sf::Vector3f origin = sf::Vector3f(0, 0, 0), sf::Vector3f dir = sf::Vector3f(0, 0, 1)) :
        _origin(origin), _dir(dir) {};
        ~Ray() = default;

        // Setters
        void setOrigin(sf::Vector3f origin) {_origin = origin;};
        void setDir(sf::Vector3f dir) {_dir = dir;};

        // Getters
        sf::Vector3f getOrigin() const {return _origin;};
        sf::Vector3f getDir() const {return _dir;};

        // Methods
        void reflect(sf::Vector3f normal, float reflectivity) {
            sf::Vector3f tmp = Math::randomDir();
            sf::Vector3f specular = _dir - 2.0f * Math::dot(_dir, normal) * normal;
            sf::Vector3f diffuse = tmp * Math::sign(Math::dot(normal, tmp));
            _dir = specular * reflectivity + diffuse * (1.0f - reflectivity);
        };
    protected:
    private:
        sf::Vector3f _origin;
        sf::Vector3f _dir;
};
