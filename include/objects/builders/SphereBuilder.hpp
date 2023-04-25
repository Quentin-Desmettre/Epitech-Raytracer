/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SphereBuilder
*/

#ifndef EPITECH_RAYTRACER_SPHEREBUILDER_HPP
#define EPITECH_RAYTRACER_SPHEREBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Sphere.hpp"

class SphereBuilder: ObjectBuilder<Sphere> {
    public:
        explicit SphereBuilder();
};

#endif //EPITECH_RAYTRACER_SPHEREBUILDER_HPP
