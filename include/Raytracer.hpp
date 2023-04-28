/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Raytracer
*/

#ifndef EPITECH_RAYTRACER_RAYTRACER_HPP
#define EPITECH_RAYTRACER_RAYTRACER_HPP
#include "scene/Scene.hpp"
#include "render/IRenderer.hpp"
#include "render/Drawer.hpp"
#include "render/RendererPool.hpp"
#include "render/PointArray.hpp"

namespace Raytracer {

    /**
     * @brief This class is the main class of the raytracer.
     *
     * Its job is to:
     * - setup the scene (using the scene builder)
     * - setup the renderers, according to the scene configuration
     * - run the renderers, and pass their output to the drawer
     */
    class Raytracer {
    public:
        Raytracer(int ac, char **av);

        void run();

    private:
        void handleEvents();
        void runClient();
        void runNormal();
        void addSphereAtPos(const sf::Vector2f &pos);
        void handleMovement(const sf::Event &ev);
        void reset(const std::unique_ptr<IRenderer> &renderer = nullptr);

        bool _isClient;
        bool _run = true;
        unsigned short _port;
        std::unique_ptr<Drawer> _drawer;
        std::unique_ptr<Scene> _scene;
        PointArray _array;
        std::unique_ptr<IRenderer> _renderer;
    };

} // Raytracer

#endif //EPITECH_RAYTRACER_RAYTRACER_HPP
