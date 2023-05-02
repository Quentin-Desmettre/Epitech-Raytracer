/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Triangle
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"
#include <array>

class Triangle : public AObject {
    public:
        Triangle(Vec3 point1 = Vec3(0, 0, 0), Vec3 point2 = Vec3(1, 0, 0), Vec3 point3 = Vec3(0, 0, 1),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Triangle() override = default;
        bool intersect(const Ray &ray) const override;
        Vec3 getIntersection(const Ray &ray) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;

        bool isPointInTriangle(const Vec3 &point) const;

    protected:
    private:
        std::array<Vec3, 3> _points;
};
