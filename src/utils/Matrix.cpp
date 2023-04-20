/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Matrix
*/

#include "utils/Matrix.hpp"

Mat4::Mat4()
{
    _matrix = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Mat4::Mat4(float matrix[16])
{
    _matrix = {
        matrix[0], matrix[1], matrix[2], matrix[3],
        matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11],
        matrix[12], matrix[13], matrix[14], matrix[15]
    };
}

Mat4 Mat4::operator*(const Mat4 &other) const
{
    Mat4 result;
    float sum = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sum = 0;
            for (int k = 0; k < 4; k++)
                sum += _matrix[i * 4 + k] * other._matrix[k * 4 + j];
            result._matrix[i * 4 + j] = sum;
        }
    }
    return result;
}

sf::Vector3f Mat4::operator*(const sf::Vector3f &vec) const
{
    sf::Vector3f result;

    result.x = _matrix[0] * vec.x + _matrix[1] * vec.y + _matrix[2] * vec.z + _matrix[3];
    result.y = _matrix[4] * vec.x + _matrix[5] * vec.y + _matrix[6] * vec.z + _matrix[7];
    result.z = _matrix[8] * vec.x + _matrix[9] * vec.y + _matrix[10] * vec.z + _matrix[11];
    return result;
}

std::array<float, 4> Mat4::operator*(const std::array<float, 4> &vec) const
{
    std::array<float, 4> result;

    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++)
            result[i] += _matrix[i * 4 + j] * vec[j];
    }
    return result;
}

Mat4 Mat4::inverse() const
{
    Mat4 inv;
    float det = 0;

    inv._matrix[0] = _matrix[5]  * _matrix[10] * _matrix[15] -
                     _matrix[5]  * _matrix[11] * _matrix[14] -
                     _matrix[9]  * _matrix[6]  * _matrix[15] +
                     _matrix[9]  * _matrix[7]  * _matrix[14] +
                     _matrix[13] * _matrix[6]  * _matrix[11] -
                     _matrix[13] * _matrix[7]  * _matrix[10];

    det = _matrix[0] * inv._matrix[0] + _matrix[1] * inv._matrix[4] + _matrix[2] * inv._matrix[8] + _matrix[3] * inv._matrix[12];
    if (det == 0)
        return Mat4();
    det = 1.0 / det;

    inv._matrix[0] = det * inv._matrix[0];
    inv._matrix[1] = det * inv._matrix[1];
    inv._matrix[2] = det * inv._matrix[2];
    inv._matrix[3] = det * inv._matrix[3];
    inv._matrix[4] = det * inv._matrix[4];
    inv._matrix[5] = det * inv._matrix[5];
    inv._matrix[6] = det * inv._matrix[6];
    inv._matrix[7] = det * inv._matrix[7];
    inv._matrix[8] = det * inv._matrix[8];
    inv._matrix[9] = det * inv._matrix[9];
    inv._matrix[10] = det * inv._matrix[10];
    inv._matrix[11] = det * inv._matrix[11];
    inv._matrix[12] = det * inv._matrix[12];
    inv._matrix[13] = det * inv._matrix[13];
    inv._matrix[14] = det * inv._matrix[14];
    inv._matrix[15] = det * inv._matrix[15];

    return inv;
}
