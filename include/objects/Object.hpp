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
        Object(Vec3 pos = Vec3(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Transparent, float intensity = 1.0f, float reflectivity = 0.0f) :
        _pos(pos), _intensity(intensity), _reflectivity(reflectivity) {
            _color = Vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
            if (emmsionColor != sf::Color::Transparent)
                _emmsionColor = Vec3(emmsionColor.r / 255.0f, emmsionColor.g / 255.0f, emmsionColor.b / 255.0f);
        };
        virtual ~Object() = default;

        // Getters
        Vec3 getPos() const {return _pos;};
        Vec3 getColor() const {return _color;};
        Vec3 getEmissionColor() const {return _emmsionColor;};
        float getEmissionIntensity() const {return _intensity;};
        float getReflectivity() const {return _reflectivity;};

        // Setters
        void setPos(Vec3 pos) {_pos = pos;};
        void setReflectivity(float reflectivity) {_reflectivity = reflectivity;};

        // Methods
        virtual bool intersect(const Ray *ray) const = 0;
        virtual Vec3 getIntersection(const Ray *ray) const = 0;
        virtual Vec3 getNormal(Vec3 inter) const = 0;
    protected:
        Vec3 _pos;
        Vec3 _color;
        Vec3 _emmsionColor;
        float _intensity = 1.0f;
        float _reflectivity = 0.0f;
    private:
};
