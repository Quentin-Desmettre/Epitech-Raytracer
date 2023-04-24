/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Sphere
*/

#pragma once

#include "Object.hpp"
#include <iostream>

class Sphere : public Object {
    public:
        Sphere(sf::Vector3f pos = sf::Vector3f(0, 0, 0), sf::Color color = sf::Color::Red, float radius = 1.0f,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Sphere() = default;
        float getRadius() const {return _radius;};
        bool intersect(const Ray *ray) const override;
        sf::Vector3f getIntersection(const Ray *ray) const override;
        sf::Vector3f getNormal(sf::Vector3f inter) const override;
        void setRadius(const float &radius) {std::cout << "radius: " << radius << std::endl; _radius = radius;};

    protected:
    private:
        float getDelta(const Ray *ray) const;
        float getIntersections(const Ray *ray) const;

        float _radius;
};
