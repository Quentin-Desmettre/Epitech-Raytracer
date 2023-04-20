/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Matrix
*/

#pragma once

#include <array>
#include <SFML/Window.hpp>

class Mat4 {
    public:
        Mat4();
        Mat4(float matrix[16]);
        ~Mat4() = default;
        Mat4 operator*(const Mat4 &other) const;
        sf::Vector3f operator*(const sf::Vector3f &vec) const;
        float &operator[](int index) {return _matrix[index];};
        std::array<float, 4> operator*(const std::array<float, 4> &vec) const;
        Mat4 inverse() const;
    protected:
    private:
        std::array<float, 16> _matrix;
};
