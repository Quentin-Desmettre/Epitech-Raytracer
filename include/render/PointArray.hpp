/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PointArray
*/

#ifndef EPITECH_RAYTRACER_POINTARRAY_HPP
#define EPITECH_RAYTRACER_POINTARRAY_HPP
#include <SFML/Graphics.hpp>
#include "Sfml.hpp"
#include <memory>

class PointArray {
public:
    explicit PointArray(sf::Vector2u size);

    sf::Uint8 *getPixels() const;

    void resize(sf::Vector2u size);

    void setStartPoint(sf::Vector2u start);

    std::size_t getSize() const;
    sf::Vector2u getSizeVector() const;

    void setPixel(sf::Vector2u pos, const Vec3 &color);
    void setPixel(sf::Vector2u pos, sf::Color color);
    sf::Color getPixel(sf::Vector2u pos) const;
    sf::Uint8 operator[](unsigned int i) const {
        return _pixels[i];
    }

private:

    // List of pixels in RGB format, ordered by column
    std::unique_ptr<sf::Uint8 []> _pixels;
    sf::Vector2u _size;
    sf::Vector2u _start;

};


#endif //EPITECH_RAYTRACER_POINTARRAY_HPP
