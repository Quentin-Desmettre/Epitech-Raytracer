/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPoint
*/

#pragma once

#include "render/Sfml.hpp"

class LightPoint {
    public:
        LightPoint(Vec3 pos, sf::Color color = sf::Color::White, float intensity = 1.0f);
        ~LightPoint();
        Vec3 getPos() const;
        sf::Color getColor() const;
        Vec3 getColorF() const;
        float getIntensity() const;
        void setPos(Vec3 pos);
        void setColor(sf::Color color);
        void setIntensity(float intensity);
    private:
        Vec3 _pos;
        sf::Color _color;
        float _intensity;
};
