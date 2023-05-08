/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightFactory
*/

#pragma once

#include "AFactory.hpp"
#include "builders/LightBuilder.hpp"

class LightFactory: public AFactory<ALight> {
    public:
        explicit LightFactory();
};
