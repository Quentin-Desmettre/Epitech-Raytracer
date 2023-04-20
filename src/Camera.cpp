/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

void Camera::move(Direction dir, float speed)
{
    switch (dir) {
        case FORWARD:
            _pos += _dir * speed;
            break;
        case BACKWARD:
            _pos -= _dir * speed;
            break;
        case LEFT:
            _pos += Math::cross(_dir, Vec3(0, 1, 0)) * speed;
            break;
        case RIGHT:
            _pos -= Math::cross(_dir, Vec3(0, 1, 0)) * speed;
            break;
        case UP:
            _pos += Vec3(0, 1, 0) * speed;
            break;
        case DOWN:
            _pos -= Vec3(0, 1, 0) * speed;
            break;
    }
}

void Camera::turn(float x, float y)
{
    _dir.x += x;
    _dir.y += y;
}
