/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Math
*/

#include "utils/Math.hpp"

sf::Vector3f Math::normalize(sf::Vector3f vec)
{
    float len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    return sf::Vector3f(vec.x / len, vec.y / len, vec.z / len);
}

float Math::dot(sf::Vector3f vec1, sf::Vector3f vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float Math::random(float min, float max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}

float Math::randomNormDistrib()
{
    float u1 = random(0, 1);
    float u2 = random(0, 1);
    return sqrt(-2.0f * log(u1)) * cos(2.0f * M_PI * u2);
}

sf::Vector3f Math::randomDir()
{
    float x = randomNormDistrib();
    float y = randomNormDistrib();
    float z = randomNormDistrib();

    return normalize(sf::Vector3f(x, y, z));
}

float Math::sign(float val)
{
    return (0 < val) - (val < 0);
}

sf::Vector3f Math::cross(sf::Vector3f vec1, sf::Vector3f vec2)
{
    return sf::Vector3f(vec1.y * vec2.z - vec1.z * vec2.y,
                        vec1.z * vec2.x - vec1.x * vec2.z,
                        vec1.x * vec2.y - vec1.y * vec2.x);
}

double Math::toRad(double deg)
{
    return deg * M_PI / 180.0;
}

sf::Vector3f Math::lerp(sf::Vector3f vec1, sf::Vector3f vec2, float t)
{
    return vec1 + t * (vec2 - vec1);
}

float Math::length(sf::Vector3f vec)
{
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

bool Math::sameSign(sf::Vector3f a, sf::Vector3f b)
{
    return (a.x * b.x >= 0) && (a.y * b.y >= 0) && (a.z * b.z >= 0);
}

sf::Vector3f Math::rotate(sf::Vector3f vec, sf::Vector3f axis, float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    float t = 1 - c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float tx = t * x;
    float ty = t * y;
    sf::Vector3f res;

    res.x = (tx * x + c) * vec.x + (tx * y - s * z) * vec.y + (tx * z + s * y) * vec.z;
    res.y = (tx * y + s * z) * vec.x + (ty * y + c) * vec.y + (ty * z - s * x) * vec.z;
    res.z = (tx * z - s * y) * vec.x + (ty * z + s * x) * vec.y + (t * z * z + c) * vec.z;
    return res;
}

Mat4 Math::lookAt(sf::Vector3f eye, sf::Vector3f center, sf::Vector3f up)
{
    sf::Vector3f f = normalize(center - eye);
    sf::Vector3f s = normalize(cross(f, up));
    sf::Vector3f u = cross(s, f);

    Mat4 res = Mat4();
    res[0] = s.x;
    res[4] = s.y;
    res[8] = s.z;
    res[1] = u.x;
    res[5] = u.y;
    res[9] = u.z;
    res[2] = -f.x;
    res[6] = -f.y;
    res[10] = -f.z;
    res[12] = -dot(s, eye);
    res[13] = -dot(u, eye);
    res[14] = dot(f, eye);
    return res;
}

Mat4 Math::perspective(float radFov, float x, float y, float near, float far)
{
    float f = 1.0f / tan(radFov / 2.0f);
    Mat4 res = Mat4();
    res[0] = f / (x / y);
    res[5] = f;
    res[10] = (far + near) / (near - far);
    res[11] = -1.0f;
    res[14] = (2.0f * far * near) / (near - far);
    return res;
}
