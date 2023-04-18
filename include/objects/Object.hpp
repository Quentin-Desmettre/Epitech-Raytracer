/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Object
*/

#pragma once

#include "Ray.hpp"
#include <SFML/Graphics.hpp>

class Object {
    public:
        Object(sf::Vector3f pos = sf::Vector3f(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f):
        _pos(pos), _intensity(intensity) {
            _color = sf::Vector3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
            _emmsionColor = sf::Vector3f(emmsionColor.r / 255.0f, emmsionColor.g / 255.0f, emmsionColor.b / 255.0f);
        };
        ~Object() = default;
        sf::Vector3f getPos() {return _pos;};
        sf::Vector3f getColor() {return _color;};
        sf::Vector3f getEmissionColor() {return _emmsionColor;};
        float getEmissionIntensity() {return _intensity;};
        virtual bool intersect(Ray *ray) = 0;
        virtual sf::Vector3f getIntersection(Ray *ray) = 0;
        virtual sf::Vector3f getNormal(sf::Vector3f inter) = 0;
    protected:
        sf::Vector3f _pos;
        sf::Vector3f _color;
        sf::Vector3f _emmsionColor;
        float _intensity = 1.0f;
    private:
};
