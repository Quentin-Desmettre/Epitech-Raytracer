/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cone
*/

#ifndef EPITECH_RAYTRACER_CONE_HPP
#define EPITECH_RAYTRACER_CONE_HPP
#include "Object.hpp"

class Cone: public Object {
public:
    bool intersect(const Ray *ray) const override {}
    sf::Vector3f getNormal(sf::Vector3f intersectionPoint) const override {}
    sf::Vector3f getIntersection(const Ray *ray) const override {}
};

#endif //EPITECH_RAYTRACER_CONE_HPP
