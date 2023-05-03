/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Drawer
*/

#ifndef EPITECH_RAYTRACER_DRAWER_HPP
#define EPITECH_RAYTRACER_DRAWER_HPP
#include <SFML/Graphics.hpp>
#include "IRenderer.hpp"
#include <memory>

namespace Raytracer {

    /**
     * @brief This class is responsible for drawing the output of the renderers.
     */
    class Drawer {
    public:
        Drawer(unsigned x, unsigned y, float antiAliasing);

        [[nodiscard]] bool isOpen() const;
        void close();
        void draw(const PointArray &array);
        void saveToFile(const std::string &filename);
        bool pollEvent(sf::Event &event);
        void resize(unsigned x, unsigned y, float antiAliasing);

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Clock _clock;
        float _antiAliasing;
    };
}

#endif //EPITECH_RAYTRACER_DRAWER_HPP
