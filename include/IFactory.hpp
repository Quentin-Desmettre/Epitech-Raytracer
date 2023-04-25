/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** IFactory
*/

#ifndef EPITECH_RAYTRACER_IFACTORY_HPP
#define EPITECH_RAYTRACER_IFACTORY_HPP

#include <string>
#include <memory>
#include "libconfig.h++"

template <typename T>
class IFactory {
    public:
        virtual ~IFactory() = default;
        virtual std::shared_ptr<T> create(const std::string &type, const libconfig::Setting &settings) = 0;
};

#endif //EPITECH_RAYTRACER_IFACTORY_HPP
