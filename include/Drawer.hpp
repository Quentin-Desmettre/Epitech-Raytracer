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
        Drawer(int x, int y);

        bool isOpen() const;
        void draw(const std::vector<std::unique_ptr<IRenderer>> &renderers);
        void draw(const sf::VertexArray &vertexArray);
        void saveToFile(const std::string &filename);

    private:
        sf::RenderWindow _window;
    };
}

#endif //EPITECH_RAYTRACER_DRAWER_HPP
