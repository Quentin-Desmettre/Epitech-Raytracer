/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cylinder
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"

class Cylinder : public AObject {
    public:
        Cylinder(Vec3 pos = Vec3(0, 0, 0),
                 Vec3 dir = Vec3(0, 1, 0),
                 float radius = 1.0f,
                 float length = INF,
                 sf::Color color = sf::Color::Red,
                 sf::Color emmsionColor = sf::Color::Black,
                 float intensity = 1.0f
        );
        ~Cylinder() override = default;
        bool intersect(const Ray &ray, Vec3 &intersection) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;

        // Setters
        void setHeight(const float &height);
        void setRadius(const float &radius);

    protected:
    private:
        Vec3 _dir;
        float _radius;
        float _length;
};
