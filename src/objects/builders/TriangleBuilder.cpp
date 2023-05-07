/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TriangleBuilder
*/

#include "objects/builders/TriangleBuilder.hpp"

TriangleBuilder::TriangleBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    this->_objSetters.push_back({"p1", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Triangle::setPoint<0>)}});
    this->_objSetters.push_back({"p2", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Triangle::setPoint<1>)}});
    this->_objSetters.push_back({"p3", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Triangle::setPoint<2>)}});

    this->_objGroupSetters.emplace_back("p1", static_cast<ABuilder<Triangle>::BuilderSetterFunc>(&TriangleBuilder::setPoint<0>));
    this->_objGroupSetters.emplace_back("p2", static_cast<ABuilder<Triangle>::BuilderSetterFunc>(&TriangleBuilder::setPoint<1>));
    this->_objGroupSetters.emplace_back("p3", static_cast<ABuilder<Triangle>::BuilderSetterFunc>(&TriangleBuilder::setPoint<2>));
#pragma GCC diagnostic pop
}
