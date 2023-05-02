/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Obj
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"

class Obj: public AObject {
    public:
        bool intersect(unused const Ray &ray) const override {return false;}
        sf::Vector3f getNormal(unused const Vec3 &inter, unused const Ray &ray) const override {return VEC3_ZERO;}
        sf::Vector3f getIntersection(unused const Ray &ray) const override {return VEC3_ZERO;}
};
