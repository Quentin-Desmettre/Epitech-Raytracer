/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjBuilder
*/

#include "objects/builders/ObjBuilder.hpp"

ObjBuilder::ObjBuilder(Scene &scene):
    _scene(scene)
{
    this->_objSetters.push_back({"path", {Type::TypeString, reinterpret_cast<ObjSetterFunc>(&Obj::setPath)}});
}
