/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#pragma once

#include "Math.hpp"
#include "Scene.hpp"
#include "lightPoint.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

#define WINDOW_SIZE sf::Vector2f(800, 800)
#define NULL_VEC_3 sf::Vector3f(0, 0, 0)
#define NB_BOUNCE 3
#define RAYS_PER_PIXEL 5.0f
#define NB_THREADS 2

inline sf::Vector3f operator*(sf::Vector3f vec, sf::Vector3f vec2) {
    return sf::Vector3f(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z);
}

inline void operator*=(sf::Vector3f &vec, sf::Vector3f vec2) {
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
}

class Renderer {
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
            Camera(sf::Vector3f pos = sf::Vector3f(0, 0, -2.0f), sf::Vector3f rot = sf::Vector3f(0, 0, 1)):
            _pos(pos), _rot(rot) {};
            ~Camera() = default;
            void setPos(sf::Vector3f pos) {_pos = pos;};
            void setRot(sf::Vector3f rot) {_rot = rot;};
            sf::Vector3f getPos() {return _pos;};
            sf::Vector3f getRot() {return _rot;};
            void move(Direction dir, float speed);
            void turn(float x, float y);
        protected:
        private:
            sf::Vector3f _pos;
            sf::Vector3f _rot;
    };
    public:
        Renderer();
        ~Renderer() = default;
        void handleMovement();
        void run(Scene *pool);
        void perThread(int startX, int endX, Scene *pool);
        void setCamera(sf::Vector3f pos = NULL_VEC_3, sf::Vector3f rot = sf::Vector3f(0, 0, 1)) {
            _camera.setPos(pos);
            _camera.setRot(rot);
        };
    protected:
    private:
        sf::Clock _clock;
        size_t _nbFrames = 0;
        Camera _camera;
        sf::RenderWindow _window;
        sf::VertexArray _vertexArray;
        sf::Vector3f _sunLight = Math::normalize(sf::Vector3f(-1, 1, 0));
        sf::Vector3f _sunColor = sf::Vector3f(1, 1, 1);
        sf::Vector3f getPixelFColor(sf::Vector2f pos, Scene *pool);
        sf::Vector3f getAmbientLight(__attribute_maybe_unused__ sf::Vector2f pos) {
            return sf::Vector3f(50 / 255.0f, 50 / 255.0f, 50 / 255.0f);
        }
        sf::Vector3f addSunLight(sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, Scene *pool, Object *obj);
        void addPixel(sf::Vector2f pos, sf::Vector3f color);
        void draw() {
            _window.draw(_vertexArray);
            _nbFrames++;
            std::cout << "Render in " << _clock.getElapsedTime().asSeconds() << "s" << std::endl;
            _clock.restart();
        };
        void drawToFile() {
            sf::Texture texture;
            texture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
            texture.update(_window);
            texture.copyToImage().saveToFile("renders/render.png");
        };
        void addLightOfPoints(sf::Vector3f &light ,sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, Scene *pool, Object *obj);
};
