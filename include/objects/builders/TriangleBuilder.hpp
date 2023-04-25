/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TriangleBuilder
*/

#ifndef EPITECH_RAYTRACER_TRIANGLEBUILDER_HPP
#define EPITECH_RAYTRACER_TRIANGLEBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Triangle.hpp"

class TriangleBuilder: ObjectBuilder<Triangle> {
    public:
        explicit TriangleBuilder() {}
};

#endif //EPITECH_RAYTRACER_TRIANGLEBUILDER_HPP
