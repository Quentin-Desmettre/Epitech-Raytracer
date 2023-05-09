/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cone
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"

class Cone : public AObject {
    public:
        Cone(Vec3 pos = Vec3(0, 0, 0),
             Vec3 dir = Vec3(0, 1, 0),
             float height = INF,
             float slope = 1,
             sf::Color color = sf::Color::Red,
             sf::Color emmsionColor = sf::Color::Black,
             float intensity = 1.0f
        );
        ~Cone() override = default;
        bool intersect(const Ray &ray, Vec3 &intersection) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;

        // Setters
        void setHeight(const float &height);
        void setSlope(const float &slope);

    protected:
    private:
        Vec3 _dir;
        float _height;
        float _slope;
};
