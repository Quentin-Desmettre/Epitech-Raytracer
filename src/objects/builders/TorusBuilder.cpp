/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TorusBuilder
*/

#include "objects/builders/TorusBuilder.hpp"

TorusBuilder::TorusBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    this->_objSetters.push_back({"radius",      {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Torus::setRadius)}});
    this->_objSetters.push_back({"thickness",   {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Torus::setThickness)}});
#pragma GCC diagnostic pop
}
