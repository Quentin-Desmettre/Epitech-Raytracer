/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Square
*/

#pragma once

#include "Triangle.hpp"
#include <array>

class Square : public AObject {
    public:
        Square(Vec3 corner1 = Vec3(0, 0, 0), Vec3 corner2 = Vec3(1, 0, 1),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Square() override = default;
        bool intersect(const Ray &ray) const override;
        Vec3 getIntersection(const Ray &ray) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;

    protected:
    private:
        std::array<Triangle, 4> _triangles;
};