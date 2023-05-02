/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** CylinderBuilder
*/

#ifndef EPITECH_RAYTRACER_CYLINDERBUILDER_HPP
#define EPITECH_RAYTRACER_CYLINDERBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Cylinder.hpp"

class CylinderBuilder: ObjectBuilder<Cylinder> {
    public:
        explicit CylinderBuilder() {}
};


#endif //EPITECH_RAYTRACER_CYLINDERBUILDER_HPP
