/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Matrix
*/

#pragma once

#include "render/Sfml.hpp"
#include "Math.hpp"
#include <array>

class Mat4 {
    public:
        Mat4();
        Mat4(std::array<float, 16> matrix);
        ~Mat4() = default;
        Mat4 operator*(const Mat4 &other) const;
        Mat4 operator*=(const Mat4 &other);
        Vec3 operator*(const Vec3 &vec) const;
        float &operator[](int index);
        float operator[](int index) const;
        float &operator()(int x, int y);
        float operator()(int x, int y) const;
        std::array<float, 4> operator*(const std::array<float, 4> &vec) const;
        Mat4 inverse() const;

        static Mat4 translate3D(const Vec3 &vec);
        static Mat4 scale3D(const Vec3 &vec);
        static Mat4 rotate3D(char axis, float angle);
        static Vec3 vecRotate(Vec3 vec, Vec3 dir, Vec3 pos);

    protected:
    private:
        std::array<float, 16> _matrix;
};
