/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SphereBuilder
*/

#include "objects/builders/SphereBuilder.hpp"

SphereBuilder::SphereBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    this->_objSetters.push_back({"radius", {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Sphere::setRadius)}});
#pragma GCC diagnostic pop
}
