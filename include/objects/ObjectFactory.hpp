/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectFactory
*/

#pragma once

#include "AFactory.hpp"
#include "builders/ObjectBuilder.hpp"

class ObjectFactory: public AFactory<AObject> {
    public:
        explicit ObjectFactory();
};
