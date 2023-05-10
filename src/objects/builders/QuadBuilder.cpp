/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** QuadBuilder
*/

#include "objects/builders/QuadBuilder.hpp"

QuadBuilder::QuadBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    this->_objSetters.push_back({"p2", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Quad::setPoint2)}});
    this->_objSetters.push_back({"p3", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Quad::setPoint3)}});
    this->_objSetters.push_back({"p4", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Quad::setPoint4)}});

    this->_objGroupSetters.emplace_back("p2", static_cast<ABuilder<Quad>::BuilderSetterFunc>(&QuadBuilder::setPosition));
    this->_objGroupSetters.emplace_back("p3", static_cast<ABuilder<Quad>::BuilderSetterFunc>(&QuadBuilder::setPosition));
    this->_objGroupSetters.emplace_back("p4", static_cast<ABuilder<Quad>::BuilderSetterFunc>(&QuadBuilder::setPosition));
#pragma GCC diagnostic pop
}
