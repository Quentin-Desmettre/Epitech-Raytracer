/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ConeBuilder
*/

#include "objects/builders/ConeBuilder.hpp"

ConeBuilder::ConeBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    _objSetters.push_back({"height", {Type::TypeFloat, reinterpret_cast<ObjSetterFunc>(&Cone::setHeight), true}});
#pragma GCC diagnostic pop
}
