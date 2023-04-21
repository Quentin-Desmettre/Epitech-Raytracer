/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectFactory
*/

#ifndef EPITECH_RAYTRACER_OBJECTFACTORY_HPP
#define EPITECH_RAYTRACER_OBJECTFACTORY_HPP
#include "AFactory.hpp"
#include "builders/ObjectBuilder.hpp"

class ObjectFactory: public AFactory<Object> {
    public:
        explicit ObjectFactory();
};

#endif //EPITECH_RAYTRACER_OBJECTFACTORY_HPP
