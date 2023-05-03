/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** CylinderBuilder
*/

#include "objects/builders/CylinderBuilder.hpp"

CylinderBuilder::CylinderBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    _objSetters.push_back({"radius",    {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Cylinder::setRadius), false}});
    _objSetters.push_back({"height",    {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Cylinder::setHeight), true}});
#pragma GCC diagnostic pop
}
