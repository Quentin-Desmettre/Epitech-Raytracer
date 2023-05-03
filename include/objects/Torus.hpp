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
    bool intersect(unused const Ray &ray) const override {return false;}
    sf::Vector3f getNormal(unused const Vec3 &inter, unused const Ray &ray) const override {return VEC3_ZERO;}
    sf::Vector3f getIntersection(unused const Ray &ray) const override {return VEC3_ZERO;}

    // Setters
    void setRadius(const float &radius);
    void setThickness(const float &thickness);

private:
    float _radius;
    float _thickness;
};
