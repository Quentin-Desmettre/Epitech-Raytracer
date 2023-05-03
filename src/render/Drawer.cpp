/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Drawer
*/

#include "render/Drawer.hpp"
#include "Print.hpp"

Raytracer::Drawer::Drawer(unsigned x, unsigned y, float antiAliasing):
    _antiAliasing(antiAliasing)
{
    _window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(x / antiAliasing, y / antiAliasing),
            "Raytracer",
            7U,
            sf::ContextSettings(0, 0, antiAliasing > 1 ? antiAliasing : 0)
    );
}

void Raytracer::Drawer::draw(const PointArray &array)
{
    // Draw from RGB pixels
    sf::Clock cl;
    sf::VertexArray vertexArray(sf::Points, array.getSize() / 3);
    unsigned x = 0, y = 0, maxY = array.getSizeVector().y;
    for (unsigned i = 0; i < array.getSize(); i += 3) {
        vertexArray[i / 3].position.x = x / _antiAliasing;
        vertexArray[i / 3].position.y = y / _antiAliasing;
        vertexArray[i / 3].color = sf::Color(array[i], array[i + 1], array[i + 2]);
        y++;
        if (y >= maxY) {
            y = 0;
            x++;
        }
    }
    Raytracer::cout << "Time to draw: " << cl.getElapsedTime().asSeconds() << "s" << std::endl;
    _window->clear();
    _window->draw(vertexArray);
    _window->display();

    // Printing render time and average
    static int nbFrames = 0;
    static float avgPerfs = 0;

    if (nbFrames == 0)
        avgPerfs = _clock.getElapsedTime().asSeconds();
    else
        avgPerfs = (avgPerfs * nbFrames + _clock.getElapsedTime().asSeconds()) / (nbFrames + 1);
    Raytracer::cout << "Render in " << _clock.getElapsedTime().asSeconds() << "s"
    << "\t(avg: " << avgPerfs << "s)" << std::endl;
    _clock.restart();
    nbFrames++;
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

void Raytracer::Drawer::resize(unsigned x, unsigned y, float antiAliasing)
{
    _window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(x / antiAliasing, y / antiAliasing),
            "Raytracer",
            7U,
            sf::ContextSettings(0, 0, antiAliasing > 1 ? antiAliasing : 0)
    );
}
