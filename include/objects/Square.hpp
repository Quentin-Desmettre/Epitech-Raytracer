/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Square
*/

#pragma once

#include "Triangle.hpp"
#include "render/Ray.hpp"
#include <array>

class Square : public AObject {
    public:
        Square(Vec3 point1 = Vec3(0, 0, 0), Vec3 point2 = Vec3(1, 0, 0), Vec3 point3 = Vec3(1, 0, 1), Vec3 point4 = Vec3(0, 0, 1),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Square() override = default;

        void setPosition(const Vec3 &position) override;
        void setPoint2(const Vec3 &point);
        void setPoint3(const Vec3 &point);
        void setPoint4(const Vec3 &point);
        bool intersect(const Ray &ray, Vec3 &intersection) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;
    protected:
    private:
        std::array<Triangle, 4> _triangles;
};
