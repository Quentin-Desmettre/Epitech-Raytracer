/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Object
*/

#pragma once

#include "Ray.hpp"
#include <SFML/Graphics.hpp>

class IObject {
    public:
        virtual ~IObject() = default;

        // Getters
        virtual Vec3 getPos() const = 0;
        virtual Vec3 getColor() const = 0;
        virtual Vec3 getEmissionColor() const = 0;
        virtual float getEmissionIntensity() const = 0;
        virtual float getReflectivity() const = 0;
        virtual float getTransparency() const = 0;

        // Setters
        virtual void setPos(Vec3 pos) = 0;
        virtual void setReflectivity(float reflectivity) = 0;
        virtual void setTransparency(float transparency) = 0;

        // Methods
        virtual bool intersect(const Ray &ray) const = 0;
        virtual Vec3 getIntersection(const Ray &ray) const = 0;
        virtual Vec3 getNormal(const Vec3 &inter, const Ray &ray) const = 0;
    protected:
        Vec3 _pos;
        Vec3 _color;
        Vec3 _emmsionColor;
        float _intensity = 1.0f;
        float _reflectivity = 0.0f;
        float _transparency = 0.0f;
    private:
};

class AObject : public IObject {
    public:
        AObject(Vec3 pos = Vec3(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Transparent, float intensity = 1.0f, float reflectivity = 0.0f) {
            _pos = pos;
            _intensity = intensity;
            _reflectivity = reflectivity;
            _color = Vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
            if (emmsionColor != sf::Color::Transparent)
                _emmsionColor = Vec3(emmsionColor.r / 255.0f, emmsionColor.g / 255.0f, emmsionColor.b / 255.0f);
        };
        virtual ~AObject() = default;

        // Getters
        Vec3 getPos() const override {return _pos;};
        Vec3 getColor() const override {return _color;};
        Vec3 getEmissionColor() const override {return _emmsionColor;};
        float getEmissionIntensity() const override {return _intensity;};
        float getReflectivity() const override {return _reflectivity;};
        float getTransparency() const override {return _transparency;};

        // Setters
        void setPos(Vec3 pos) override {_pos = pos;};
        void setReflectivity(float reflectivity) override {_reflectivity = reflectivity;};
        void setTransparency(float transparency) override {_transparency = transparency;};

        // Methods
        bool intersect(unused const Ray &ray) const override {return false;};
        Vec3 getIntersection(unused const Ray &ray) const override {return VEC3_ZERO;};
        Vec3 getNormal(unused const Vec3 &inter, unused const Ray &ray) const override {return VEC3_ZERO;};
    protected:
    private:
};

inline bool operator==(const AObject &lhs, const AObject &rhs)
{
    return lhs.getPos() == rhs.getPos() && lhs.getColor() == rhs.getColor() &&
    lhs.getEmissionColor() == rhs.getEmissionColor() && lhs.getEmissionIntensity() == rhs.getEmissionIntensity() &&
    lhs.getReflectivity() == rhs.getReflectivity();
}

inline bool operator!=(const AObject &lhs, const AObject &rhs)
{
    return lhs.getPos() != rhs.getPos() || lhs.getColor() != rhs.getColor() ||
    lhs.getEmissionColor() != rhs.getEmissionColor() || lhs.getEmissionIntensity() != rhs.getEmissionIntensity() ||
    lhs.getReflectivity() != rhs.getReflectivity();
}
