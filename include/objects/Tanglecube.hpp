/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Tanglecube
*/

#ifndef EPITECH_RAYTRACER_TANGLECUBE_HPP
#define EPITECH_RAYTRACER_TANGLECUBE_HPP
#include "Object.hpp"

class Tanglecube: public Object {
public:
    bool intersect(const Ray *ray) const override {}
    sf::Vector3f getNormal(sf::Vector3f intersectionPoint) const override {}
    sf::Vector3f getIntersection(const Ray *ray) const override {}
};

#endif //EPITECH_RAYTRACER_TANGLECUBE_HPP