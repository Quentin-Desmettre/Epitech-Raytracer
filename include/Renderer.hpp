/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#pragma once

#include "Math.hpp"
#include "ObjectPool.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

#define WINDOW_SIZE sf::Vector2f(800, 800)
#define NULL_VEC_3 sf::Vector3f(0, 0, 0)
#define NB_BOUNCE 5
#define RAYS_PER_PIXEL 5.0f
#define NB_THREADS 2

sf::Vector3f operator*(sf::Vector3f vec, sf::Vector3f vec2) {
    return sf::Vector3f(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z);
}

void operator*=(sf::Vector3f &vec, sf::Vector3f vec2) {
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
            void move(Direction dir, float speed) {
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
            };
            void turn(float x, float y) {
                _rot.x += x;
                _rot.y += y;
                // if (_rot.y > 89.0f)
                //     _rot.y = 89.0f;
                // if (_rot.y < -89.0f)
                //     _rot.y = -89.0f;
                // _rot = Math::normalize(_rot);
            };
        protected:
        private:
            sf::Vector3f _pos;
            // rotation of the camera in degrees (x = roll, y = pitch, z = yaw)
            sf::Vector3f _rot;
    };
    public:
        Renderer() {
            for (int i = 0; i < WINDOW_SIZE.x; i++)
                for (int j = 0; j < WINDOW_SIZE.y; j++)
                    _vertexArray.append(sf::Vertex(sf::Vector2f(i, j), sf::Color::Black));
        };
        ~Renderer() = default;
        void handleMovement() {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                _camera.move(Camera::FORWARD, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                _camera.move(Camera::BACKWARD, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                _camera.move(Camera::LEFT, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                _camera.move(Camera::RIGHT, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                _camera.move(Camera::UP, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                _camera.move(Camera::DOWN, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                _camera.turn(0, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                _camera.turn(0, -0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                _camera.turn(-0.1f, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                _camera.turn(0.1f, 0);
        };
        void run(ObjectPool &pool) {
            _window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "RayTracer");
            while (_window.isOpen()) {
                sf::Event event;
                while (_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        _window.close();
                    else
                        handleMovement();
                }
                _window.clear();
                std::vector<std::thread> threads;
                const int subset_size = WINDOW_SIZE.x / NB_THREADS;
                perThread(0, WINDOW_SIZE.x, pool);
                // for (uint i = 0; i < NB_THREADS; i++)
                //     threads.push_back(std::thread(&Renderer::perThread, this, i * subset_size,
                //     (i + 1) * subset_size - subset_size / 2, std::ref(pool)));
                // for (auto &thread : threads)
                //     thread.join();
                // threads.clear();
                // for (uint i = 0; i < NB_THREADS; i++)
                //     threads.push_back(std::thread(&Renderer::perThread, this, i * subset_size + subset_size / 2,
                //     i + 1 >= NB_THREADS ? WINDOW_SIZE.x : (i + 1) * subset_size, std::ref(pool)));
                // for (auto &thread : threads)
                //     thread.join();
                draw();
                drawToFile();
                _window.display();
            }
        };
        void perThread(int startX, int endX, ObjectPool &pool) {
            for (int x = startX; x < endX; x++)
                for (int y = 0; y < WINDOW_SIZE.y; y++) {
                    sf::Vector3f colors = sf::Vector3f(0, 0, 0);
                    for (float i = 0; i < RAYS_PER_PIXEL; i++)
                        colors += getPixelFColor(sf::Vector2f(x, y), pool);
                    colors /= RAYS_PER_PIXEL;
                    addPixel(sf::Vector2f(x, y), colors);
                }
        };
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
        sf::Vector3f getPixelFColor(sf::Vector2f pos, ObjectPool &pool) {
            sf::Vector3f rayColor = sf::Vector3f(1, 1, 1);
            sf::Vector3f light = NULL_VEC_3;
            Ray ray = Ray(_camera.getPos(), _camera.getRot() +
            sf::Vector3f(pos.x / WINDOW_SIZE.x - 0.5f, pos.y / WINDOW_SIZE.y - 0.5f, 1));
            for (int bounces = 0; bounces <= NB_BOUNCE; bounces++) {
                Object *obj = pool.getClosest(ray);
                if (obj) {
                    sf::Vector3f inter = obj->getIntersection(ray);
                    sf::Vector3f normal = obj->getNormal(inter);
                    float strength = std::max(Math::dot(normal, -ray.getDir()), 0.0f);
                    light += obj->getEmissionColor() * rayColor * strength * obj->getEmissionIntensity();
                    rayColor *= obj->getColor();
                    ray.setOrigin(inter);
                    ray.reflect(normal);
                    if (obj->getEmissionColor() != NULL_VEC_3)
                        break;
                } else {
                    light += rayColor * getAmbientLight(pos);
                    break;
                }
            }
            return light;
        };
        sf::Vector3f getAmbientLight(__attribute_maybe_unused__ sf::Vector2f pos) {
            return sf::Vector3f(15 / 255.0f, 15 / 255.0f, 15 / 255.0f);
        }
        void addPixel(sf::Vector2f pos, sf::Vector3f color) {
            color *= 255.0f;
            color.x = std::min(color.x, 255.0f);
            color.y = std::min(color.y, 255.0f);
            color.z = std::min(color.z, 255.0f);
            if (_nbFrames != 0) {
                sf::Color old = _vertexArray[pos.x * WINDOW_SIZE.x + pos.y].color;
                sf::Vector3f oldColor = sf::Vector3f(old.r, old.g, old.b);
                if (oldColor == NULL_VEC_3 || color == NULL_VEC_3)
                    color += oldColor;
                else {
                    float weight = 1.0f / (_nbFrames + 1);
                    color = oldColor * (1 - weight) + color * weight;
                }
            }
            _vertexArray[pos.x * WINDOW_SIZE.x + pos.y].color = sf::Color(color.x, color.y, color.z);
        };
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
            texture.copyToImage().saveToFile("render.png");
        };
};
