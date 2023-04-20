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
        Plane(Vec3 corner1 = Vec3(0, 0, 0), Vec3 corner2 = Vec3(1, 0, 1),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Plane() = default;
        bool intersect(const Ray *ray) const override;
        Vec3 getIntersection(const Ray *ray) const override;
        Vec3 getNormal(Vec3 inter) const override;

    protected:
    private:
        std::array<Triangle, 2> _triangles;
};
