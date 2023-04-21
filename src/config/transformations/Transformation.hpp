/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ATransformation
*/

#ifndef EPITECH_RAYTRACER_ATRANSFORMATION_HPP
#define EPITECH_RAYTRACER_ATRANSFORMATION_HPP
#include "../ITransformation.hpp"

class Transformation: public ITransformation {
public:
    explicit Transformation(const std::string &name);
    std::string getName() const override;
    Math::Matrix getMatrix() const override;
    void setMatrix(const Math::Matrix &matrix);

private:
    std::string _name;
    Math::Matrix _matrix;
};

#endif //EPITECH_RAYTRACER_ATRANSFORMATION_HPP
