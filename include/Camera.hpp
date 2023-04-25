/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Camera
*/

#pragma once

#include "utils/Math.hpp"
#include "utils/Matrix.hpp"

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
        Camera(Vec3 pos = Vec3(0, 0, 0), Vec3 rot = Vec3(0, 0, 0), sf::Vector2u size = sf::Vector2u(800, 800)):
        _pos(pos), _rot(rot), _size(size) {updateRayDirs();};
        ~Camera() = default;


        // Setters
        void setPos(Vec3 pos) {
            _pos = pos;
            updateRayDirs();
        };
        void setRot(Vec3 rot) {
            _rot = rot;
            updateRayDirs();
        };
        void setResolution(sf::Vector2u size) {_size = size;};

        // Getters
        sf::Vector2u getResolution() const {return _size;};
        Vec3 getPos() const {return _pos;};
        Vec3 getRot() const {return _rot;};
        Vec3 getRayDir(sf::Vector2f pos) const {
            return _rayDirs[(int)pos.x * (int)WINDOW_SIZE.y + (int)pos.y];
        };

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
};