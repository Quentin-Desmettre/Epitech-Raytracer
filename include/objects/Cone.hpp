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
        Cone(Vec3 pos = Vec3(0, 0, 0), Vec3 dir = Vec3(0, 1, 0), float height = INF, bool isCapped = false,
        sf::Color color = sf::Color::Red, sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Cone() override = default;
        bool intersect(const Ray &ray) const override;
        Vec3 getIntersection(const Ray &ray) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;

    protected:
    private:
        Vec3 _dir;
        float _height;
        bool _isCapped;
};
