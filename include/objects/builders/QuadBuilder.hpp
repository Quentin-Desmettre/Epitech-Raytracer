/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** QuadBuilder
*/

#pragma once

#include "ObjectBuilder.hpp"
#include "objects/Quad.hpp"

class QuadBuilder: ObjectBuilder<Quad> {
    public:
        explicit QuadBuilder();
};
