/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Object
*/

#pragma once

#include "Ray.hpp"
#include <SFML/Graphics.hpp>

class Object {
    public:
        Object(sf::Vector3f pos = sf::Vector3f(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f, float reflectivity = 0.0f) :
        _pos(pos), _intensity(intensity), _reflectivity(reflectivity) {
            _color = sf::Vector3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
            _emmsionColor = sf::Vector3f(emmsionColor.r / 255.0f, emmsionColor.g / 255.0f, emmsionColor.b / 255.0f);
        };
        virtual ~Object() = default;

        void setPosition(const sf::Vector3f &pos) {_pos = pos;};
        void setEmissionColor(const sf::Color &color) {_emmsionColor = sf::Vector3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);};
        void setTransparency(const float &transparency) {};
        void setReflectivity(const float &reflectivity) {_reflectivity = reflectivity;};
        void setEmissionIntensity(const float &intensity) {_intensity = intensity;};
        void setTransformations(const std::vector<sf::Transform> &transformations) {};

        sf::Vector3f getPos() const {return _pos;};
        sf::Vector3f getColor() const {return _color;};
        sf::Vector3f getEmissionColor() const {return _emmsionColor;};
        float getEmissionIntensity() const {return _intensity;};
        float getReflectivity() const {return _reflectivity;};
        virtual bool intersect(const Ray *ray) const = 0;
        virtual sf::Vector3f getIntersection(const Ray *ray) const = 0;
        virtual sf::Vector3f getNormal(sf::Vector3f inter) const = 0;
    protected:
        sf::Vector3f _pos;
        sf::Vector3f _color;
        sf::Vector3f _emmsionColor;
        float _intensity = 1.0f;
        float _reflectivity = 0.0f;
    private:
};
