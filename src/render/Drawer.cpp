/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Drawer
*/

#include "render/Drawer.hpp"
#include "Print.hpp"

Raytracer::Drawer::Drawer(int x, int y, float antiAliasing) :
_window(sf::VideoMode(x / antiAliasing, y / antiAliasing), "Raytracer", 7U, sf::ContextSettings(0, 0, antiAliasing > 1 ? antiAliasing : 0)),
_antiAliasing(antiAliasing)
{
}

void Raytracer::Drawer::draw(const PointArray &array)
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
    // Draw from RGB pixels
    sf::Clock cl;
    sf::VertexArray vertexArray(sf::Points, array.getSize() / 3);
    unsigned x = 0, y = 0, maxY = array.getSizeVector().y;
    for (unsigned i = 0; i < array.getSize(); i += 3) {
        vertexArray[i / 3].position.x = x;
        vertexArray[i / 3].position.y = y;
        vertexArray[i / 3].color = sf::Color(array[i], array[i + 1], array[i + 2]);
        // apply anti-aliasing through supersampling
        // if (_antiAliasing > 1) {
        //     Vec3 tmp;
        //     for (int j = 0; j < _antiAliasing; j++) {
        //         for (int k = 0; k < _antiAliasing; k++) {
        //             tmp += Vec3(array[(i + j * 3) * (uint)_antiAliasing + k * 3], array[(i + j * 3) * (uint)_antiAliasing + k * 3 + 1], array[(i + j * 3) * (uint)_antiAliasing + k * 3 + 2]);
        //         }
        //     }
        //     tmp /= _antiAliasing * _antiAliasing;
        //     vertexArray[i / 3].color = sf::Color(tmp.x, tmp.y, tmp.z);
        // }
        y++;
        if (y >= maxY) {
            y = 0;
            x++;
        }
    }
    for (unsigned i = 0; i < array.getSize(); i += 3) {
        vertexArray[i / 3].position.x /= _antiAliasing;
        vertexArray[i / 3].position.y /= _antiAliasing;
    }
    Raytracer::cout << "Time to draw: " << cl.getElapsedTime().asSeconds() << "s" << std::endl;
    _window.draw(vertexArray);
    _window.display();
    // #ifdef DEBUG
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
    // #endif
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

bool Raytracer::Drawer::pollEvent(sf::Event &event)
{
    return _window.pollEvent(event);
}

void Raytracer::Drawer::close()
{
    _window.close();
}
