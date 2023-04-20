/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#pragma once

#include "Sfml.hpp"
#include "Scene.hpp"
#include "LightPoint.hpp"
#include "Camera.hpp"
#include <iostream>
#include <thread>

#define NB_BOUNCE 3
#define RAYS_PER_PIXEL 5.0f

class Renderer {
    public:
        Renderer();
        ~Renderer() = default;
        void run(Scene *pool);
        void useThreads(bool use = false) {_threads = use;};
        void smoothImage(bool smooth = true) {_smooth = smooth;};
        void setCamera(Vec3 pos = VEC_NULL, Vec3 dir = Vec3(0, 0, 1)) {
            _camera.setPos(pos);
            _camera.setDir(dir);
        };
    protected:
    private:
        Camera _camera;
        sf::RenderWindow _window;
        sf::VertexArray _vertexArray;
        Vec3 _sunColor = Vec3(1, 1, 1);
        Vec3 _sunLight = Math::normalize(Vec3(-1, 1, 0));
        sf::Clock _clock;
        bool _smooth = true;
        bool _threads = false;
        size_t _nbFrames = 0;

        // Getters
        Vec3 getPixelFColor(sf::Vector2f pos, const Scene *pool) const ;
        Vec3 getAmbientLight(__attribute_maybe_unused__ sf::Vector2f pos) const {
            return Vec3(50 / 255.0f, 50 / 255.0f, 50 / 255.0f);
        }

        // Setters
        Vec3 addSunLight(Vec3 normal, Vec3 inter,
        Vec3 color, const Scene *pool, const Object *obj) const;
        Vec3 addLightOfPoints(Vec3 normal, Vec3 inter,
        Vec3 color, const Scene *pool, const Object *obj) const;
        void addPixel(sf::Vector2f pos, Vec3 color);

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
