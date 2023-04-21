/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ATransformation
*/

#include "transformations/Transformation.hpp"

#include <utility>

Transformation::Transformation(std::string name):
    _name(std::move(name))
{
}

std::string Transformation::getName() const
{
    return _name;
}

std::vector<Math::Matrix<4, 4>> Transformation::getMatrices() const
{
    return _matrices;
}

void Transformation::setMatrices(const std::vector<Math::Matrix<4, 4>> &matrices)
{
    _matrices = matrices;
}
