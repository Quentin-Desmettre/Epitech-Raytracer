/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SquareBuilder
*/

#include "objects/builders/SquareBuilder.hpp"

SquareBuilder::SquareBuilder()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    this->_objSetters.push_back({"p2", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Square::setPoint2)}});
    this->_objSetters.push_back({"p3", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Square::setPoint3)}});
    this->_objSetters.push_back({"p4", {Type::TypeGroup, reinterpret_cast<ObjSetterFunc>(&Square::setPoint4)}});

    this->_objGroupSetters.emplace_back("p2", static_cast<ABuilder<Square>::BuilderSetterFunc>(&SquareBuilder::setPosition));
    this->_objGroupSetters.emplace_back("p3", static_cast<ABuilder<Square>::BuilderSetterFunc>(&SquareBuilder::setPosition));
    this->_objGroupSetters.emplace_back("p4", static_cast<ABuilder<Square>::BuilderSetterFunc>(&SquareBuilder::setPosition));
#pragma GCC diagnostic pop
}
