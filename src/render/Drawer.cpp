/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Drawer
*/

#include "render/Drawer.hpp"
#include "Print.hpp"

Raytracer::Drawer::Drawer(unsigned x, unsigned y)
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(x, y), "Raytracer");
}

void Raytracer::Drawer::draw(const PointArray &array)
{
    sf::Event event{};

    // Draw from RGB pixels
    sf::Clock cl;
    sf::VertexArray vertexArray(sf::Points, array.getSize() / 3);
    unsigned x = 0, y = 0, maxY = array.getSizeVector().y;
    for (unsigned i = 0; i < array.getSize(); i += 3) {
        vertexArray[i / 3].position.x = x;
        vertexArray[i / 3].position.y = y;
        vertexArray[i / 3].color = sf::Color(array.getPixels()[i], array.getPixels()[i + 1], array.getPixels()[i + 2]);
        y++;
        if (y >= maxY) {
            y = 0;
            x++;
        }
    }
    Raytracer::cout << "Time to draw: " << cl.getElapsedTime().asSeconds() << "s" << std::endl;
    _window->draw(vertexArray);
    _window->display();
    #ifdef DEBUG
        static sf::Clock clock;
        static int _nbFrames = 0;
        static float avgPerfs = 0;

        if (_nbFrames == 0)
            avgPerfs = clock.getElapsedTime().asSeconds();
        else
            avgPerfs = (avgPerfs * _nbFrames + clock.getElapsedTime().asSeconds()) / (_nbFrames + 1);
        Raytracer::cout << "Render in " << clock.getElapsedTime().asSeconds() << "s"
        << "\t(avg: " << avgPerfs << "s)" << std::endl;
        clock.restart();
        _nbFrames++;
    #endif
}

void Raytracer::Drawer::saveToFile(const std::string &filename)
{
    sf::Texture texture;
    texture.create(_window->getSize().x, _window->getSize().y);
    texture.update(*_window);
    texture.copyToImage().saveToFile(filename);
}

bool Raytracer::Drawer::isOpen() const
{
    return _window->isOpen();
}

bool Raytracer::Drawer::pollEvent(sf::Event &event)
{
    return _window->pollEvent(event);
}

void Raytracer::Drawer::close()
{
    _window->close();
}

void Raytracer::Drawer::resize(unsigned x, unsigned y)
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(x, y), "Raytracer");
}
