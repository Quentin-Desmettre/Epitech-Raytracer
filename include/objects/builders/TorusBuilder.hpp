/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TorusBuilder
*/

#ifndef EPITECH_RAYTRACER_TORUSBUILDER_HPP
#define EPITECH_RAYTRACER_TORUSBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Torus.hpp"

class TorusBuilder: ObjectBuilder<Torus> {
    public:
        explicit TorusBuilder();
};

#endif //EPITECH_RAYTRACER_TORUSBUILDER_HPP
