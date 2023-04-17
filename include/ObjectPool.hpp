/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectPool
*/

#pragma once

#include "Ray.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Object {
    public:
        Object(sf::Vector3f pos = sf::Vector3f(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f):
        _pos(pos), _intensity(intensity) {
            _color = sf::Vector3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
            _emmsionColor = sf::Vector3f(emmsionColor.r / 255.0f, emmsionColor.g / 255.0f, emmsionColor.b / 255.0f);
        };
        ~Object() = default;
        sf::Vector3f getPos() {return _pos;};
        sf::Vector3f getColor() {return _color;};
        sf::Vector3f getEmissionColor() {return _emmsionColor;};
        float getEmissionIntensity() {return _intensity;};
        virtual bool intersect(Ray ray) = 0;
        virtual sf::Vector3f getIntersection(Ray ray) = 0;
        virtual sf::Vector3f getNormal(sf::Vector3f inter) = 0;
    protected:
        sf::Vector3f _pos;
        sf::Vector3f _color;
        sf::Vector3f _emmsionColor;
        float _intensity = 1.0f;
    private:
};

class Sphere : public Object {
    public:
        Sphere(sf::Vector3f pos = sf::Vector3f(0, 0, 0), sf::Color color = sf::Color::Red, float radius = 1.0f,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f): Object(pos, color, emmsionColor, intensity), _radius(radius) {};
        ~Sphere() = default;
        float getRadius() {return _radius;};
        bool intersect(Ray ray) override {
            a = Math::dot(ray.getDir(), ray.getDir());
            b = 2 * Math::dot(ray.getDir(), ray.getOrigin() - _pos);
            c = Math::dot(ray.getOrigin() - _pos, ray.getOrigin() - _pos) - _radius * _radius;

            return b * b - 4.0f * a * c >= 0;
        };
        sf::Vector3f getIntersection(Ray ray) override {
            float delta = b * b - 4.0f * a * c;
            float t = (-b - sqrt(delta)) / (2.0f * a);

            if (t < 0)
                return sf::Vector3f(0, 0, 0);
            return ray.getOrigin() + ray.getDir() * t;
        };
        sf::Vector3f getNormal(sf::Vector3f inter) override {
            return Math::normalize(inter - _pos);
        };
    protected:
    private:
        float _radius;
        float a;
        float b;
        float c;
};

class ObjectPool {
    public:
        ObjectPool() = default;
        ~ObjectPool() = default;
        void addObject(Object *obj) {_pool.push_back(obj);};
        std::vector<Object *> getPool() {return _pool;};
        Object *getClosest(Ray ray) {
            Object *closest = nullptr;
            float dist = __FLT_MAX__;

            for (auto &obj : _pool) {
                if (!obj->intersect(ray) || dist < Math::length(ray.getOrigin() - obj->getPos()))
                    continue;
                dist = Math::length(ray.getOrigin() - obj->getPos());
                closest = obj;
            }
            return closest;
        };
    protected:
    private:
        std::vector<Object *> _pool;
};
