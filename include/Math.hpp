/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** maths
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

namespace Math
{
    inline sf::Vector3f normalize(sf::Vector3f vec) {
        float len = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
        return sf::Vector3f(vec.x / len, vec.y / len, vec.z / len);
    }
    inline float dot(sf::Vector3f vec1, sf::Vector3f vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }
    inline float random(float min, float max) {
        return min + (rand() / (RAND_MAX / (max - min)));
    }
    inline float randomNormDistrib() {
        float u1 = random(0, 1);
        float u2 = random(0, 1);
        return sqrt(-2.0f * log(u1)) * cos(2.0f * M_PI * u2);
    }
    inline sf::Vector3f randomDir() {
        float x = randomNormDistrib();
        float y = randomNormDistrib();
        float z = randomNormDistrib();

        return normalize(sf::Vector3f(x, y, z));
    }
    inline float sign(float val) {
        return (0 < val) - (val < 0);
    }
    inline sf::Vector3f cross(sf::Vector3f vec1, sf::Vector3f vec2) {
        return sf::Vector3f(vec1.y * vec2.z - vec1.z * vec2.y,
                            vec1.z * vec2.x - vec1.x * vec2.z,
                            vec1.x * vec2.y - vec1.y * vec2.x);
    }
    inline double toRad(double deg) {
        return deg * M_PI / 180.0;
    }
    inline sf::Vector3f lerp(sf::Vector3f vec1, sf::Vector3f vec2, float t) {
        return vec1 + t * (vec2 - vec1);
    }
    inline float length(sf::Vector3f vec) {
        return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    }
    inline bool sameSign(sf::Vector3f a, sf::Vector3f b) {
        return (a.x * b.x >= 0) && (a.y * b.y >= 0) && (a.z * b.z >= 0);
    }


    template<std::size_t N, std::size_t M>
    class Matrix {
    public:

        Matrix(const std::initializer_list<std::initializer_list<double>> &list) {
            std::size_t i = 0, j = 0;

            for (auto &row: list) {
                j = 0;
                for (auto &elem: row) {
                    _matrix[i][j] = elem;
                    j++;
                }
                i++;
            }
        }
        Matrix() {
            for (std::size_t i = 0; i < N; i++)
                std::fill(_matrix[i].begin(), _matrix[i].end(), 0);
        }
        Matrix(const Matrix &other) {
            _matrix = other._matrix;
        }

        // matrix mul / add / sub
        Matrix operator*(const Matrix &other) const {
            Matrix result;

            for (std::size_t i = 0; i < N; i++) {
                for (std::size_t j = 0; j < M; j++) {
                    for (std::size_t k = 0; k < M; k++) {
                        result._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
                    }
                }
            }
            return result;
        }
        Matrix operator+(const Matrix &other) const {
            Matrix result;

            for (std::size_t i = 0; i < N; i++) {
                for (std::size_t j = 0; j < M; j++) {
                    result._matrix[i][j] = _matrix[i][j] + other._matrix[i][j];
                }
            }
            return result;
        }
        Matrix operator-(const Matrix &other) const {
            Matrix result;

            for (std::size_t i = 0; i < N; i++) {
                for (std::size_t j = 0; j < M; j++) {
                    result._matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
                }
            }
            return result;
        }

        // Assignment add/sub/mul
        Matrix &operator=(const Matrix &other) {
            _matrix = other._matrix;
            return *this;
        }
        Matrix &operator+=(const Matrix &other) {
            *this = *this + other;
            return *this;
        }
        Matrix &operator-=(const Matrix &other) {
            *this = *this - other;
            return *this;
        }
        Matrix &operator*=(const Matrix &other) {
            *this = *this * other;
            return *this;
        }

        // Scalar operations
        Matrix operator*(double scalar) const {
            Matrix result;

            for (std::size_t i = 0; i < N; i++) {
                for (std::size_t j = 0; j < M; j++) {
                    result._matrix[i][j] = _matrix[i][j] * scalar;
                }
            }
            return result;
        }
        Matrix operator/(double scalar) const {
            Matrix result;

            for (std::size_t i = 0; i < N; i++) {
                for (std::size_t j = 0; j < M; j++) {
                    result._matrix[i][j] = _matrix[i][j] / scalar;
                }
            }
            return result;
        }

        // Get an element
        double &operator()(std::size_t i, std::size_t j) {
            if (i >= N || j >= M)
                throw std::out_of_range("Matrix index out of range");
            return _matrix[i][j];
        }
        double operator()(std::size_t i, std::size_t j) const {
            if (i >= N || j >= M)
                throw std::out_of_range("Matrix index out of range");
            return _matrix[i][j];
        }

        // Static methods
        static Matrix identity() {
            if (N != M)
                throw std::invalid_argument("Identity matrix must be square");

            Matrix result;
            for (std::size_t i = 0; i < N; i++)
                result._matrix[i][i] = 1;
            return result;
        }

        static Matrix<4, 4> translate3D(double x, double y, double z) {
            Matrix<4, 4> result = Matrix<4, 4>::identity();

            result._matrix[0][3] = x;
            result._matrix[1][3] = y;
            result._matrix[2][3] = z;
            return result;
        }

        static Matrix<4, 4> rotate3D(char axis, double angle) {
            Matrix<4, 4> result = Matrix<4, 4>::identity();

            double rad = angle * M_PI / 180;
            switch (axis) {
                case 'x':
                    result._matrix[1][1] = cos(rad);
                    result._matrix[1][2] = -sin(rad);
                    result._matrix[2][1] = sin(rad);
                    result._matrix[2][2] = cos(rad);
                    break;
                case 'y':
                    result._matrix[0][0] = cos(rad);
                    result._matrix[0][2] = sin(rad);
                    result._matrix[2][0] = -sin(rad);
                    result._matrix[2][2] = cos(rad);
                    break;
                case 'z':
                    result._matrix[0][0] = cos(rad);
                    result._matrix[0][1] = -sin(rad);
                    result._matrix[1][0] = sin(rad);
                    result._matrix[1][1] = cos(rad);
                    break;
                default:
                    throw std::invalid_argument("Invalid axis");
            }
            return result;
        }

        static Matrix<4, 4> scale3D(double x, double y, double z) {
            Matrix<4, 4> result = Matrix<4, 4>::identity();

            result._matrix[0][0] = x;
            result._matrix[1][1] = y;
            result._matrix[2][2] = z;
            return result;
        }

    private:
        std::array<std::array<double, M>, N> _matrix;
    };

}
