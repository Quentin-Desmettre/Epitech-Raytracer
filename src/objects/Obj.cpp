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
std::regex Obj::_trianglesRegex = std::regex("f ([0-9]+)/?[0-9]*/?[0-9]* ([0-9]+)/?[0-9]*/?[0-9]* ([0-9]+)/?[0-9]*/?[0-9]*");
std::regex Obj::_squaresRegex = std::regex("f ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+)");

void Obj::createTriangle(unsigned long x, unsigned long y, unsigned long z)
{
    if (x > _vertices.size())
        throw std::runtime_error("Invalid vertex index");
    if (y > _vertices.size())
        throw std::runtime_error("Invalid vertex index");
    if (z > _vertices.size())
        throw std::runtime_error("Invalid vertex index");
    Triangle triangle(_vertices[x], _vertices[y], _vertices[z], colorInt, emmsionColorInt, _light.getIntensity());

    _triangles.emplace_back(triangle);
    _scene->addObject(std::make_unique<Triangle>(triangle));
}

void Obj::setPath(const std::string &path)
{
    std::ifstream ifs(path);
    std::string line;
    std::smatch match;
    Vec3 pos = _pos;
    colorInt = {sf::Uint8(_color.x * 255), sf::Uint8(_color.y * 255), sf::Uint8(_color.z * 255)};
    emmsionColorInt = {sf::Uint8(_light.getColor().x * 255), sf::Uint8(_light.getColor().y * 255), sf::Uint8(_light.getColor().z * 255)};
    if (!ifs.is_open())
        return;
    std::cout << "Loading obj: " << path << std::endl;
    while (std::getline(ifs, line)) {
        if (std::regex_match(line, _verticesRegex)) {
            std::regex_search(line, match, _verticesRegex);
            Vec3 tmp = Vec3(-std::stof(match[1]), -std::stof(match[2]), -std::stof(match[3]));
            _vertices.emplace_back(tmp + pos);
            continue;
        }
        if (std::regex_match(line, _squaresRegex)) {
            std::regex_search(line, match, _squaresRegex);
            createTriangle(std::stoul(match[1]) - 1, std::stoul(match[2]) - 1, std::stoul(match[3]) - 1);
            createTriangle(std::stoul(match[1]) - 1, std::stoul(match[3]) - 1, std::stoul(match[4]) - 1);
            continue;
        }
        if (std::regex_match(line, _trianglesRegex)) {
            std::regex_search(line, match, _trianglesRegex);
            createTriangle(std::stoul(match[3]) - 1, std::stoul(match[2]) - 1, std::stoul(match[1]) - 1);
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

bool Obj::intersect(const unused Ray &ray) const
{
    return false;
}

Vec3 Obj::getIntersection(const unused Ray &ray) const
{
    return VEC3_ZERO;
}

Vec3 Obj::getNormal(const unused Vec3 &inter, const unused Ray &ray) const
{
    return VEC3_ZERO;
}
