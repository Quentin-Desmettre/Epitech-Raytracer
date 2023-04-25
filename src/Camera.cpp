/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

void Camera::move(Direction movement, float speed, bool &reset)
{
    Vec3 dir = _rayDirs[WINDOW_SIZE.y * 0.5 + WINDOW_SIZE.x * 0.5 * WINDOW_SIZE.y];

    switch (movement) {
        case FORWARD:
            _pos += dir * speed;
            reset = true;
            break;
        case BACKWARD:
            _pos -= dir * speed;
            reset = true;
            break;
        case LEFT:
            _pos += Math::cross(dir, Vec3(0, 1, 0)) * speed;
            reset = true;
            break;
        case RIGHT:
            _pos -= Math::cross(dir, Vec3(0, 1, 0)) * speed;
            reset = true;
            break;
        case UP:
            _pos -= Vec3(0, 1, 0) * speed;
            reset = true;
            break;
        case DOWN:
            _pos += Vec3(0, 1, 0) * speed;
            reset = true;
            break;
        default:
            break;
    }
}

void Camera::turn(float x, float y, bool &reset)
{
    _rot.x += x;
    _rot.y += y;
    updateRayDirs();
    reset = true;
}

void Camera::updateRayDirs() {
    _rayDirs.clear();
    for (int i = 0; i < WINDOW_SIZE.x; i++) {
        for (int j = 0; j < WINDOW_SIZE.y; j++) {
            Vec3 rayDir = Math::normalize(Vec3(i - WINDOW_SIZE.x / 2,
            j - WINDOW_SIZE.y / 2, WINDOW_SIZE.x / 2));
            _rayDirs.push_back(Math::normalize(Mat4::vecRotate(rayDir, _rot, _pos)));
        }
    }
};
