/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Obj
*/

#include "objects/Obj.hpp"
#include <fstream>
#include "scene/Scene.hpp"

std::regex Obj::_verticesRegex = std::regex("v (-?[0-9]+.[0-9]+) (-?[0-9]+.[0-9]+) (-?[0-9]+.[0-9]+)");
std::regex Obj::_trianglesRegex = std::regex("f ([0-9]+) ([0-9]+) ([0-9]+)");


void Obj::setPath(const std::string &path)
{
    std::ifstream ifs(path);
    std::string line;
    std::smatch match;
    Vec3 pos = _pos;

    if (!ifs.is_open())
        return;
    sf::Color color(_color.x * 255, _color.y * 255, _color.z * 255);
    sf::Color emmsionColor(_emmsionColor.x * 255, _emmsionColor.y * 255, _emmsionColor.z * 255);
    std::cout << "Loading obj: " << path << std::endl;
    while (std::getline(ifs, line)) {
        if (std::regex_match(line, _verticesRegex)) {
            std::regex_search(line, match, _verticesRegex);
            Vec3 tmp = Vec3(std::stof(match[1]), std::stof(match[2]), std::stof(match[3]));
            _vertices.emplace_back(tmp + pos);
            continue;
        }
        if (std::regex_match(line, _trianglesRegex)) {
            std::regex_search(line, match, _trianglesRegex);
            Triangle triangle(_vertices[std::stoi(match[1]) - 1], _vertices[std::stoi(match[2]) - 1], _vertices[std::stoi(match[3]) - 1], color, emmsionColor, _intensity);
            _scene->addObject(std::make_unique<Triangle>(triangle));
            _scene->test();
            continue;
        }
        std::cout << "Unknown line: " << line << std::endl;
    }
    ifs.close();
}

Obj::Obj(Scene *scene, Vec3 pos,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _scene = scene;
}

bool Obj::intersect(const Ray &ray) const
{
    return false;
}

Vec3 Obj::getIntersection(const Ray &ray) const
{
    return VEC3_ZERO;
}

Vec3 Obj::getNormal(const Vec3 &inter, const Ray &ray) const
{
    return VEC3_ZERO;
}
