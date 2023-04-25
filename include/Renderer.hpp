/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#pragma once

#include "utils/Math.hpp"
#include "scene/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Sfml.hpp"
#include "LightPoint.hpp"
#include "objects/Sphere.hpp"
#include "lights/ILight.hpp"
#include "Camera.hpp"
#include <thread>
#include <memory>

#define NB_BOUNCE 3
#define RAYS_PER_PIXEL 5.0f
#define NB_THREADS std::thread::hardware_concurrency()

class Renderer {
    public:
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
    typedef std::shared_ptr<Renderer::Camera> SharedCamera;
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
        Vec3 color, const Scene *pool, const AObject *obj) const;
        Vec3 addLightOfPoints(Vec3 normal, Vec3 inter,
        Vec3 color, const Scene *pool, const AObject *obj) const;
        void addPixel(sf::Vector2f pos, Vec3 color);
        void addSphereAtPos(sf::Vector2f pos, Scene *pool);

        // Others
        void resetPixels() {_nbFrames = 1;};
        void handleMovement(sf::Event event);
        void perThread(int startX, int endX, const Scene *pool);
        void draw();
        void drawToFile();
};
