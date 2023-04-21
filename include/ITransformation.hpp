/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ITransformation
*/

#ifndef EPITECH_RAYTRACER_ITRANSFORMATION_HPP
#define EPITECH_RAYTRACER_ITRANSFORMATION_HPP
#include "Math.hpp"

class ITransformation {
public:
    virtual ~ITransformation() = default;
    virtual std::string getName() const = 0;

    /**
     * @brief Get the Matrices object
     * @return The list of transformations to apply, in order
     */
    virtual std::vector<Math::Matrix<4, 4>> getMatrices() const = 0;
};


#endif //EPITECH_RAYTRACER_ITRANSFORMATION_HPP
