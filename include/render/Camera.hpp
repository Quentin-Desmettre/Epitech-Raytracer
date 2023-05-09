/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#pragma once

#include "utils/Math.hpp"
#include "utils/Matrix.hpp"

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
        Camera(Vec3 pos = Vec3(0, 0, 0), Vec3 rot = Vec3(0, 0, 0), sf::Vector2u size = sf::Vector2u(800, 800)):
        _pos(pos), _rot(rot), _size(size), _antiAliasing(1) {};
        ~Camera() = default;

        // Setters
        void setPos(Vec3 pos);
        void setRot(Vec3 rot);
        void setFov(float fov);
        void setResolution(sf::Vector2u size);
        void setAntiAliasing(float antiAliasing);

        // Getters
        sf::Vector2u getResolution() const {return _size;};
        Vec3 getPos() const {return _pos;};
        Vec3 getRot() const {return _rot;};
        float getAntiAliasing() const {return _antiAliasing;};
        Vec3 getRayDir(sf::Vector2f pos) const;

        // Methods
        void move(Direction dir, float speed, bool &reset);
        void turn(float x, float y, bool &reset);
        void updateRayDirs();
    protected:
    private:
        Vec3 _pos;
        Vec3 _rot;
        sf::Vector2u _size;
        sf::Vector2f _view;
        std::vector<Vec3> _rayDirs;
        float _antiAliasing;
        float _fov;
};