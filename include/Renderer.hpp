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
#include "objects/Sphere.hpp"
#include "Camera.hpp"
#include <thread>

#define NB_BOUNCE 3
#define RAYS_PER_PIXEL 5.0f
#define NB_THREADS std::thread::hardware_concurrency()

class Renderer {
    public:
        Renderer();
        ~Renderer() = default;
        void run(Scene *pool, Camera &camera);
        void useThreads(bool use = false) {_threads = use;};
        void smoothImage(bool smooth = true) {_smooth = smooth;};
        void setCamera(Camera camera) {_camera = camera;};
    protected:
    private:
        // Attributes
        Camera _camera;
        sf::RenderWindow _window;
        sf::VertexArray _vertexArray;
        std::vector<Vec3> _pixels;
        sf::Clock clock;
        std::vector<std::thread> _threadPool;

        // Settings
        Vec3 _sunColor = Vec3(1, 1, 1);
        Vec3 _sunLight = Math::normalize(Vec3(-1, 1, -0.5));
        bool _smooth = true;
        bool _threads = false;
        size_t _nbFrames = 1;

        // Getters
        Vec3 getPixelFColor(sf::Vector2f pos, const Scene *pool) const ;
        Vec3 getAmbientLight(unused sf::Vector2f pos) const {
            return Vec3(50 / 255.0f, 50 / 255.0f, 50 / 255.0f);
        }

        // Setters
        Vec3 addSunLight(Vec3 normal, Vec3 inter,
        Vec3 color, const Scene *pool, const Object *obj) const;
        Vec3 addLightOfPoints(Vec3 normal, Vec3 inter,
        Vec3 color, const Scene *pool, const Object *obj) const;
        void addPixel(sf::Vector2f pos, Vec3 color);
        void addSphereAtPos(sf::Vector2f pos, Scene *pool);

        // Others
        void resetPixels() {
            for (size_t i = 0; i < _pixels.size(); i++)
                _pixels[i] = Vec3(0, 0, 0);
            _nbFrames = 1;
        };
        void handleMovement(sf::Event event);
        void perThread(int startX, int endX, const Scene *pool);
        void draw();
        void drawToFile() {
            sf::Texture texture;
            texture.create(_window.getSize().x, _window.getSize().y);
            texture.update(_window);
            texture.copyToImage().saveToFile("renders/render.png");
        };
};
