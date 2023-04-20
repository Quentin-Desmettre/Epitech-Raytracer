/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#pragma once

#include "utils/Math.hpp"
#include "utils/Matrix.hpp"
#include <SFML/Graphics.hpp>

#define WINDOW_SIZE sf::Vector2f(800, 800)

class Camera {
    public:
        enum Direction {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT,
            UP,
            DOWN
        };
        Camera(sf::Vector3f pos = sf::Vector3f(0, 0, -2.0f), sf::Vector3f dir = sf::Vector3f(0, 0, 1)):
        _pos(pos), _dir(dir) {};
        ~Camera() = default;

        // Setters
        void setPos(sf::Vector3f pos) {_pos = pos;};
        void setDir(sf::Vector3f dir) {_dir = dir;};

        // Getters
        sf::Vector3f getPos() {return _pos;};
        sf::Vector3f getDir() {return _dir;};

        // Methods
        void move(Direction dir, float speed);
        void turn(float x, float y);
    protected:
    private:
        sf::Vector3f _pos;
        sf::Vector3f _dir;
};