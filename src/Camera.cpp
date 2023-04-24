/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#include "scene/Scene.hpp"

void Camera::move(Direction dir, float speed)
{
    switch (dir) {
        case FORWARD:
            _pos += _rot * speed;
            break;
        case BACKWARD:
            _pos -= _rot * speed;
            break;
        case LEFT:
            _pos += Math::cross(_rot, sf::Vector3f(0, 1, 0)) * speed;
            break;
        case RIGHT:
            _pos -= Math::cross(_rot, sf::Vector3f(0, 1, 0)) * speed;
            break;
        case UP:
            _pos += sf::Vector3f(0, 1, 0) * speed;
            break;
        case DOWN:
            _pos -= sf::Vector3f(0, 1, 0) * speed;
            break;
    }
}

void Camera::turn(float x, float y)
{
    _rot.x += x;
    _rot.y += y;
}
