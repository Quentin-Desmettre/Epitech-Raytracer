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
        Sphere(Vec3 pos = Vec3(0, 0, 0), sf::Color color = sf::Color::Red, float radius = 1.0f,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Sphere() = default;
        float getRadius() const {return _radius;};
        bool intersect(const Ray *ray) const override;
        Vec3 getIntersection(const Ray *ray) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;
    protected:
    private:
        float getDelta(const Ray *ray) const;
        float getIntersections(const Ray *ray) const;

        float _radius;
};
