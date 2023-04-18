/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Triangle
*/

#pragma once

#include "Object.hpp"
#include <array>

class Triangle : public Object {
    public:
        Triangle(sf::Vector3f point1 = sf::Vector3f(0, 0, 0), sf::Vector3f point2 = sf::Vector3f(1, 0, 0), sf::Vector3f point3 = sf::Vector3f(0, 0, 1),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Triangle() = default;
        bool intersect(Ray *ray) override;
        sf::Vector3f getIntersection(Ray *ray) override;
        sf::Vector3f getNormal(sf::Vector3f inter) override;
    protected:
    private:
        std::array<sf::Vector3f, 3> _points;
        Ray *_lastRay;
};
