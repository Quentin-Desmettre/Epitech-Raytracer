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

namespace Raytracer {

    /**
     * @brief This class is responsible for drawing the output of the renderers.
     */
    class Drawer {
    public:
        Drawer(int x, int y, float antiAliasing);

        bool isOpen() const;
        void close();
        void draw(const PointArray &array);
        void saveToFile(const std::string &filename);
        bool pollEvent(sf::Event &event);

    private:
        sf::RenderWindow _window;
        float _antiAliasing;
    };
}

#endif //EPITECH_RAYTRACER_DRAWER_HPP
