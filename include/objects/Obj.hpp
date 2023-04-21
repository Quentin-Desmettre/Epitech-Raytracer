/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Obj
*/

#ifndef EPITECH_RAYTRACER_OBJ_HPP
#define EPITECH_RAYTRACER_OBJ_HPP
#include "Object.hpp"

class Obj: public Object {
public:
    bool intersect(const Ray *ray) const override {}
    sf::Vector3f getNormal(sf::Vector3f intersectionPoint) const override {}
    sf::Vector3f getIntersection(const Ray *ray) const override {}
};

#endif //EPITECH_RAYTRACER_OBJ_HPP
