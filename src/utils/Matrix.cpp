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

Mat4::Mat4(std::array<float, 16> matrix)
{
    _matrix = matrix;
}

float &Mat4::operator[](int index)
{
    return _matrix[index];
}

float &Mat4::operator()(int x, int y)
{
    return _matrix[x * 4 + y];
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

Vec3 Mat4::operator*(const Vec3 &vec) const
{
    Vec3 result;

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

Vec3 Mat4::vecRotate(Vec3 vec, Vec3 dir, Vec3 pos)
{
    Mat4 mat = Mat4({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -pos.x, -pos.y, -pos.z, 1
    });
    Mat4 mat2 = Mat4({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        pos.x, pos.y, pos.z, 1
    });
    Mat4 mat3 = Mat4({
        1, 0, 0, 0,
        0, static_cast<float>(cos(dir.x)), static_cast<float>(-sin(dir.x)), 0,
        0, static_cast<float>(sin(dir.x)), static_cast<float>(cos(dir.x)), 0,
        0, 0, 0, 1
    });
    Mat4 mat4 = Mat4({
        static_cast<float>(cos(dir.y)), 0, static_cast<float>(sin(dir.y)), 0,
        0, 1, 0, 0,
        static_cast<float>(-sin(dir.y)), 0, static_cast<float>(cos(dir.y)), 0,
        0, 0, 0, 1
    });
    Mat4 mat5 = Mat4({
        static_cast<float>(cos(dir.z)), static_cast<float>(-sin(dir.z)), 0, 0,
        static_cast<float>(sin(dir.z)), static_cast<float>(cos(dir.z)), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    });
    return mat5 * mat4 * mat3 * mat2 * mat * vec;
    // In one matrix
//    float cosDirX = cosf(dir.x);
//    float cosDirY = cosf(dir.y);
//    float cosDirZ = cosf(dir.z);
//    float sinDirX = sinf(dir.x);
//    float sinDirY = sinf(dir.y);
//    float sinDirZ = sinf(dir.z);
//    Mat4 mat = Mat4({
//        cosDirY * cosDirZ,                                  -cosDirY * sinDirZ,                                 sinDirY,            0,
//        cosDirX * sinDirZ + sinDirX * sinDirY * cosDirZ,    cosDirX * cosDirZ - sinDirX * sinDirY * sinDirZ,    -sinDirX * cosDirY, 0,
//        sinDirX * sinDirZ - cosDirX * sinDirY * cosDirZ,    sinDirX * cosDirZ + cosDirX * sinDirY * sinDirZ,    cosDirX * cosDirY,  0,
//        0,                                                  0,                                                  0,                  1
//    });
//    return mat * vec;
}

Mat4 Mat4::translate3D(const Vec3 &vec)
{
    return Mat4({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        vec.x, vec.y, vec.z, 1
    });
}

Mat4 Mat4::scale3D(const Vec3 &vec)
{
    return Mat4({
        vec.x, 0, 0, 0,
        0, vec.y, 0, 0,
        0, 0, vec.z, 0,
        0, 0, 0, 1
    });
}

Mat4 Mat4::rotate3D(char axis, double angle)
{
    switch (axis) {
        case 'x':
            return Mat4({
                1, 0, 0, 0,
                0, static_cast<float>(cos(angle)), static_cast<float>(-sin(angle)), 0,
                0, static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0,
                0, 0, 0, 1
            });
        case 'y':
            return Mat4({
                static_cast<float>(cos(angle)), 0, static_cast<float>(sin(angle)), 0,
                0, 1, 0, 0,
                static_cast<float>(-sin(angle)), 0, static_cast<float>(cos(angle)), 0,
                0, 0, 0, 1
            });
        case 'z':
            return Mat4({
                static_cast<float>(cos(angle)), static_cast<float>(-sin(angle)), 0, 0,
                static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            });
        default:
            throw std::invalid_argument("Invalid axis");
    }
}
