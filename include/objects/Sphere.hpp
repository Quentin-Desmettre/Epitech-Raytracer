/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Sphere
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"
#include <iostream>

class Sphere : public AObject {
    public:
        Sphere(Vec3 pos = Vec3(0, 0, 0), sf::Color color = sf::Color::Red, float radius = 1.0f,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Sphere() override = default;
        float getRadius() const {return _radius;};
        void setRadius(const float &radius) {_radius = radius;};
        void setTransparency(const bool &transparency) override;
        bool intersect(const Ray &ray, Vec3 &intersection) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;

    protected:
    private:
        float getDelta(const Ray &ray) const;
        float getIntersections(const Ray &ray) const;

        float _radius;
};
