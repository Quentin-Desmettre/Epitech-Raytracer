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
        bool intersect(unused const Ray &ray, Vec3 &intersection) const override {return false;}
        Vec3 getNormal(unused const Vec3 &inter, unused const Ray &ray) const override {return VEC3_ZERO;}
};
