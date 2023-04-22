/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Plane
*/

#pragma once

#include "Object.hpp"

class Plane : public Object {
    public:
        Plane(Vec3 pos = Vec3(0, 0, 0), Vec3 dir = Vec3(0, 1, 0),
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Plane() = default;
        bool intersect(const Ray &ray) const override;
        Vec3 getIntersection(const Ray &ray) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;
    protected:
    private:
        Vec3 _dir;
};
