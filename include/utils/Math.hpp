/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** maths
*/

#pragma once

#include "Matrix.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

namespace Math
{
    sf::Vector3f normalize(sf::Vector3f vec);
    float dot(sf::Vector3f vec1, sf::Vector3f vec2);
    float random(float min, float max);
    float randomNormDistrib();
    sf::Vector3f randomDir();
    float sign(float val);
    sf::Vector3f cross(sf::Vector3f vec1, sf::Vector3f vec2);
    double toRad(double deg);
    sf::Vector3f lerp(sf::Vector3f vec1, sf::Vector3f vec2, float t);
    float length(sf::Vector3f vec);
    bool sameSign(sf::Vector3f a, sf::Vector3f b);
    sf::Vector3f rotate(sf::Vector3f vec, sf::Vector3f axis, float angle);
    Mat4 lookAt(sf::Vector3f eye, sf::Vector3f center, sf::Vector3f up);
    Mat4 perspective(float radFov, float x, float y, float near, float far);
}
