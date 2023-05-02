/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SphereBuilder
*/

#include "objects/builders/SphereBuilder.hpp"

SphereBuilder::SphereBuilder()
{
    this->_objSetters.push_back({"radius", {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Sphere::setRadius)}});
}
