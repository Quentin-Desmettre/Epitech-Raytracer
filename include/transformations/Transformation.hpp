/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ATransformation
*/

#ifndef EPITECH_RAYTRACER_TRANSFORMATION_HPP
#define EPITECH_RAYTRACER_TRANSFORMATION_HPP
#include "../ITransformation.hpp"
#include "objects/Object.hpp"

class Transformation: public ITransformation {
public:
    explicit Transformation(std::string name);

    std::string getName() const override;
    std::vector<Math::Matrix<4, 4>> getMatrices() const override;

    void setMatrices(const std::vector<Math::Matrix<4, 4>> &matrices);

private:
    std::string _name;
    std::vector<Math::Matrix<4, 4>> _matrices;
};

#endif //EPITECH_RAYTRACER_TRANSFORMATION_HPP
