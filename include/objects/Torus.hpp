/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Torus
*/

#ifndef EPITECH_RAYTRACER_TORUS_HPP
#define EPITECH_RAYTRACER_TORUS_HPP
#include "Object.hpp"

class Torus: public Object {
public:
    bool intersect(const Ray *ray) const override {}
    sf::Vector3f getNormal(sf::Vector3f intersectionPoint) const override {}
    sf::Vector3f getIntersection(const Ray *ray) const override {}
};

#endif //EPITECH_RAYTRACER_TORUS_HPP
