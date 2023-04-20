/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPoint
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class LightPoint {
    public:
        LightPoint(sf::Vector3f pos, sf::Color color = sf::Color::White, float intensity = 1.0f);
        ~LightPoint();
        sf::Vector3f getPos();
        sf::Color getColor();
        sf::Vector3f getColorF();
        float getIntensity();
        void setPos(sf::Vector3f pos);
        void setColor(sf::Color color);
        void setIntensity(float intensity);
    private:
        sf::Vector3f _pos;
        sf::Color _color;
        float _intensity;
};


