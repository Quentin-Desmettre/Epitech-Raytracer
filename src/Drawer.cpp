/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Drawer
*/

#include "Drawer.hpp"
#include <thread>

Raytracer::Drawer::Drawer(int x, int y) : _window(sf::VideoMode(x, y), "Raytracer")
{
}

void Raytracer::Drawer::draw(const std::vector<std::unique_ptr<IRenderer>> &renderers)
{
    for (auto &renderer : renderers)
        _window.draw(renderer->getVertexArray());
    _window.display();
}

void Raytracer::Drawer::draw(const sf::VertexArray &vertexArray)
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
    _window.draw(vertexArray);
    _window.display();
    #if DEBUG
        static sf::Clock clock;
        static int _nbFrames = 0;
        static float avgPerfs = 0;

        if (_nbFrames == 0)
            avgPerfs = clock.getElapsedTime().asSeconds();
        else
            avgPerfs = (avgPerfs * _nbFrames + clock.getElapsedTime().asSeconds()) / (_nbFrames + 1);
        std::cout << "Render in " << clock.getElapsedTime().asSeconds() << "s"
        << "\t(avg: " << avgPerfs << "s)" << std::endl;
        clock.restart();
        _nbFrames++;
    #endif
}

void Raytracer::Drawer::saveToFile(const std::string &filename)
{
    sf::Texture texture;
    texture.create(_window.getSize().x, _window.getSize().y);
    texture.update(_window);
    texture.copyToImage().saveToFile(filename);
}

bool Raytracer::Drawer::isOpen() const
{
    return _window.isOpen();
}
