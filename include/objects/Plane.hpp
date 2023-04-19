/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Plane
*/

#pragma once

#include "Triangle.hpp"
#include <array>

class Plane : public Object {
    public:
        Plane(sf::Vector3f corner1 = sf::Vector3f(0, 0, 0), sf::Vector3f corner2 = sf::Vector3f(1, 0, 1),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Plane() = default;
        bool intersect(const Ray *ray) const override;
        sf::Vector3f getIntersection(const Ray *ray) const override;
        sf::Vector3f getNormal(sf::Vector3f inter) const override;

    protected:
    private:
        std::array<Triangle, 2> _triangles;
};
