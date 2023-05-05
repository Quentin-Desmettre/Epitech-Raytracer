/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Obj
*/

#pragma once

#include "Object.hpp"
#include "render/Ray.hpp"
#include "Triangle.hpp"
#include <regex>
#include "scene/Scene.hpp"

class Obj: public AObject {
    public:
        Obj(Scene *scene = nullptr, Vec3 pos = Vec3(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Black, float intensity = 1.0f);
        ~Obj() override = default;

        bool intersect(const Ray &ray) const override;
        Vec3 getNormal(const Vec3 &inter, const Ray &ray) const override;
        Vec3 getIntersection(const Ray &ray) const override;
        void setPath(const std::string &path);

        static std::regex _verticesRegex;
        static std::regex _trianglesRegex;
        static std::regex _trianglesRegexx;
        static std::regex _squaresRegex;

    private:
        std::string _path;
        std::vector<Vec3> _vertices;
        std::vector<Triangle> _triangles;
        Scene *_scene;

};
