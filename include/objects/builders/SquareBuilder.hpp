/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SquareBuilder
*/

#pragma once

#include "ObjectBuilder.hpp"
#include "objects/Square.hpp"

class SquareBuilder: ObjectBuilder<Square> {
    public:
        explicit SquareBuilder();
};
