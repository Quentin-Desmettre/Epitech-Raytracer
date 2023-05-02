/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ILight
*/

#pragma once

#include "render/Sfml.hpp"
#include "../utils/Math.hpp"

class IObject;
class Scene;
class Ray;

class ILight {
    public:
        ~ILight() = default;

        virtual Vec3 getColor() const = 0;
        virtual float getIntensity() const = 0;
        virtual void setColor(const sf::Color &color) = 0;
        virtual void setColor(const Vec3 &color) = 0;
        virtual void setIntensity(const float &intensity) = 0;
        virtual Vec3 illuminate(const Vec3 &normal, const Vec3 &rayColor, const Vec3 &rayDir) const = 0;
        virtual Vec3 illuminate(const Vec3 &normal, const Vec3 &inter, const Vec3 &color, const Scene &pool, const IObject *obj) const = 0;
    protected:
        Vec3 _color;
        float _intensity;
    private:
};

class ALight : public ILight {
    public:
        ~ALight() = default;

        Vec3 getColor() const {return _color;};
        float getIntensity() const {return _intensity;};
        void setColor(const sf::Color &color) {_color = Vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);};
        void setColor(const Vec3 &color) {_color = color;};
        void setIntensity(const float &intensity) {_intensity = intensity;};
        Vec3 illuminate(unused const Vec3 &normal, unused const Vec3 &rayColor, unused const Vec3 &rayDir) const {return VEC3_ZERO;};
        Vec3 illuminate(unused const Vec3 &normal, unused const Vec3 &inter, unused const Vec3 &color,
        unused const Scene &pool, unused const IObject *obj) const {return VEC3_ZERO;};
    protected:
    private:
};
