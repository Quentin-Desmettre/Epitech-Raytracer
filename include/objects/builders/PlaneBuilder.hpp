/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PlaneBuilder
*/

#ifndef EPITECH_RAYTRACER_PLANEBUILDER_HPP
#define EPITECH_RAYTRACER_PLANEBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Plane.hpp"

class PlaneBuilder: ObjectBuilder<Plane> {
    public:
        explicit PlaneBuilder();
};

#endif //EPITECH_RAYTRACER_PLANEBUILDER_HPP
