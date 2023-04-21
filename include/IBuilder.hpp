/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** IBuilder
*/

#ifndef EPITECH_RAYTRACER_IBUILDER_HPP
#define EPITECH_RAYTRACER_IBUILDER_HPP

#include <memory>
#include "libconfig.h++"

template <typename T>
class IBuilder {
public:
    virtual ~IBuilder() = default;
    virtual std::unique_ptr<T> build(const libconfig::Setting &settings) = 0;
};

#endif //EPITECH_RAYTRACER_IBUILDER_HPP
