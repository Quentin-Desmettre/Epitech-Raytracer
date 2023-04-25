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
    std::vector<Mat4> getMatrices() const override;

    void setMatrices(const std::vector<Mat4> &matrices);

private:
    std::string _name;
    std::vector<Mat4> _matrices;
};

#endif //EPITECH_RAYTRACER_TRANSFORMATION_HPP
