/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Sphere
*/

#pragma once

#include "Object.hpp"

class Sphere : public Object {
    public:
        Sphere(sf::Vector3f pos = sf::Vector3f(0, 0, 0), sf::Color color = sf::Color::Red, float radius = 1.0f,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Sphere() = default;
        float getRadius() {return _radius;};
        bool intersect(Ray *ray) override;
        sf::Vector3f getIntersection(Ray *ray) override;
        sf::Vector3f getNormal(sf::Vector3f inter) override;
    protected:
    private:
        float _radius;
        float a;
        float b;
        float c;
        float _delta;
        Ray *_lastRay;
};
