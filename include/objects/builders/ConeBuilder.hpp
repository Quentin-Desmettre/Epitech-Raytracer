/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ConeBuilder
*/

#ifndef EPITECH_RAYTRACER_CONEBUILDER_HPP
#define EPITECH_RAYTRACER_CONEBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Cone.hpp"

class ConeBuilder: ObjectBuilder<Cone> {
    public:
        explicit ConeBuilder() {}
};

#endif //EPITECH_RAYTRACER_CONEBUILDER_HPP
