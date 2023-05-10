/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Torus
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"

class Torus: public AObject {
public:
    bool intersect(unused const Ray &ray, Vec3 &intersection) const override;
    Vec3 getNormal(unused const Vec3 &inter, unused const Ray &ray) const override;

    // Setters
    void setRadius(const float &radius);
    void setThickness(const float &thickness);

private:
    float _radius;
    float _thickness;
};
