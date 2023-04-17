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
    sf::Vector3f normalize(sf::Vector3f vec) {
        float len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
        return sf::Vector3f(vec.x / len, vec.y / len, vec.z / len);
    }
    float dot(sf::Vector3f vec1, sf::Vector3f vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }
    float random(float min, float max) {
        return min + (rand() / (RAND_MAX / (max - min)));
    }
    float randomNormDistrib() {
        float u1 = random(0, 1);
        float u2 = random(0, 1);
        return sqrt(-2.0f * log(u1)) * cos(2.0f * M_PI * u2);
    }
    sf::Vector3f randomDir() {
        float x = randomNormDistrib();
        float y = randomNormDistrib();
        float z = randomNormDistrib();

        return normalize(sf::Vector3f(x, y, z));
    }
    float sign(float val) {
        return (0 < val) - (val < 0);
    }
    sf::Vector3f cross(sf::Vector3f vec1, sf::Vector3f vec2) {
        return sf::Vector3f(vec1.y * vec2.z - vec1.z * vec2.y,
                            vec1.z * vec2.x - vec1.x * vec2.z,
                            vec1.x * vec2.y - vec1.y * vec2.x);
    }
    double toRad(double deg) {
        return deg * M_PI / 180.0;
    }
    sf::Vector3f lerp(sf::Vector3f vec1, sf::Vector3f vec2, float t) {
        return vec1 + t * (vec2 - vec1);
    }
    float length(sf::Vector3f vec) {
        return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    }
}
