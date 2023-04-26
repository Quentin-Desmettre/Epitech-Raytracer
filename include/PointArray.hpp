/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PointArray
*/

#ifndef EPITECH_RAYTRACER_POINTARRAY_HPP
#define EPITECH_RAYTRACER_POINTARRAY_HPP
#include <SFML/Graphics.hpp>

class PointArray {
public:
    explicit PointArray(sf::Vector2u size);

    void resize(sf::Vector2u size);

    sf::Uint8 *getPixels() const;

    std::size_t getSize() const;
    sf::Vector2u getSizeVector() const;

    void setPixel(sf::Vector2u pos, const sf::Vector3f &color);
    void setPixel(sf::Vector2u pos, sf::Color color);
    sf::Color getPixel(sf::Vector2u pos) const;

private:

    // List of pixels in RGB format, ordered by column
    std::unique_ptr<sf::Uint8 []> _pixels;
    sf::Vector2u _size;

};


#endif //EPITECH_RAYTRACER_POINTARRAY_HPP
