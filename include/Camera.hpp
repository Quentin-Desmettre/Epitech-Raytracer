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
        Camera(Vec3 pos = Vec3(0, 0, -2.0f), Vec3 dir = Vec3(0, 0, 1)):
        _pos(pos), _dir(dir) {};
        ~Camera() = default;

        // Setters
        void setPos(Vec3 pos) {_pos = pos;};
        void setDir(Vec3 dir) {_dir = dir;};

        // Getters
        Vec3 getPos() const {return _pos;};
        Vec3 getDir() const {return _dir;};

        // Methods
        void move(Direction dir, float speed);
        void turn(float x, float y);
    protected:
    private:
        Vec3 _pos;
        Vec3 _dir;
};