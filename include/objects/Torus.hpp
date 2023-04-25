/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Torus
*/

#ifndef EPITECH_RAYTRACER_TORUS_HPP
#define EPITECH_RAYTRACER_TORUS_HPP
#include "Object.hpp"

class Torus: public AObject {
public:
    bool intersect(const Ray &ray) const override {}
    sf::Vector3f getNormal(const Vec3 &inter, const Ray &ray) const override {}
    sf::Vector3f getIntersection(const Ray &ray) const override {}
};

#endif //EPITECH_RAYTRACER_TORUS_HPP
