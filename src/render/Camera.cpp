/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#include "render/Camera.hpp"

void Camera::move(Direction movement, float speed, bool &reset)
{
    Vec3 dir = _rayDirs[_size.y * 0.5 + _size.x * 0.5 * _size.y];

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
    reset = true;
}

void Camera::updateRayDirs() {
    _rayDirs.clear();
    _rayDirs.reserve(_size.x * _size.y);

    float aspectRatio = (float)_size.x / _size.y;
    float halfFovTan = std::tan(_fov / 2.0f);

    for (uint i = 0; i < _size.x; i++) {
        for (uint j = 0; j < _size.y; j++) {
            float x = (2.0f * (i + 0.5f) / _size.x - 1.0f) * aspectRatio * halfFovTan;
            float y = (2.0f * (j + 0.5f) / _size.y - 1.0f) * halfFovTan;

            // Use this one when we fixed the inversed Y
//            float y = (1.0f - 2.0f * ((float)j + 0.5f) / (float)_size.y) * halfFovTan;
            Vec3 rayDir = Math::normalize(Vec3(x, y, 1.0f));
            _rayDirs.push_back(Math::normalize(Mat4::vecRotate(rayDir, _rot, _pos)));
        }
    }
}

// Setters
void Camera::setPos(Vec3 pos)
{
    _pos = pos;
}

void Camera::setRot(Vec3 rot)
{
    _rot = rot;
}

void Camera::setFov(float fov)
{
    _fov = fov * M_PI / 180.0f;
}

void Camera::setResolution(sf::Vector2u size)
{
    _size = sf::Vector2u(size.x * _antiAliasing, size.y * _antiAliasing);
}

void Camera::setAntiAliasing(float antiAliasing)
{
    _antiAliasing = antiAliasing;
    _size = sf::Vector2u(_size.x * _antiAliasing, _size.y * _antiAliasing);
}

Vec3 Camera::getRayDir(sf::Vector2f pos) const
{
    return _rayDirs[(int)pos.x * _size.y + (int)pos.y];
}
