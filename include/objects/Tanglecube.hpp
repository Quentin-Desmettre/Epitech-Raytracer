/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Tanglecube
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"

class Tanglecube: public AObject {
    public:
        bool intersect(unused const Ray &ray, unused Vec3 &intersection) const override {return false;}
        sf::Vector3f getNormal(unused const Vec3 &inter, unused const Ray &ray) const override {return VEC3_ZERO;}
};
