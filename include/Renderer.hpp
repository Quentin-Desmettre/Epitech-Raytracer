/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#pragma once

#include "Scene.hpp"
#include "LightPoint.hpp"
#include "Camera.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

#define NULL_VEC_3 sf::Vector3f(0, 0, 0)
#define NB_BOUNCE 3
#define RAYS_PER_PIXEL 5.0f

inline sf::Vector3f operator*(sf::Vector3f vec, sf::Vector3f vec2) {
    return sf::Vector3f(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z);
}

inline void operator*=(sf::Vector3f &vec, sf::Vector3f vec2) {
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
}

class Renderer {
    public:
        Renderer();
        ~Renderer() = default;
        void run(Scene *pool);
        void smoothImage(bool smooth = true) {_smooth = smooth;};
        void setCamera(sf::Vector3f pos = NULL_VEC_3, sf::Vector3f dir = sf::Vector3f(0, 0, 1)) {
            _camera.setPos(pos);
            _camera.setDir(dir);
        };
    protected:
    private:
        Camera _camera;
        sf::RenderWindow _window;
        sf::VertexArray _vertexArray;
        sf::Vector3f _sunColor = sf::Vector3f(1, 1, 1);
        sf::Vector3f _sunLight = Math::normalize(sf::Vector3f(-1, 1, 0));
        sf::Clock _clock;
        bool _smooth = true;
        size_t _nbFrames = 0;

        // Getters
        sf::Vector3f getPixelFColor(sf::Vector2f pos, const Scene *pool);
        sf::Vector3f getAmbientLight(__attribute_maybe_unused__ sf::Vector2f pos) {
            return sf::Vector3f(50 / 255.0f, 50 / 255.0f, 50 / 255.0f);
        }

        // Setters
        sf::Vector3f addSunLight(sf::Vector3f normal, sf::Vector3f inter,
        sf::Vector3f color, const Scene *pool, const Object *obj);
        void addLightOfPoints(sf::Vector3f &light ,sf::Vector3f normal,
        sf::Vector3f inter, sf::Vector3f color, const Scene *pool, const Object *obj);
        void addPixel(sf::Vector2f pos, sf::Vector3f color);

        // Others
        void handleMovement();
        void perThread(int startX, int endX, Scene *pool);
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
};
