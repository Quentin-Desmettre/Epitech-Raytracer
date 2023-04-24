/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LocalRenderer
*/

#include "LocalRenderer.hpp"
#include <SFML/Network.hpp>

Raytracer::LocalRenderer::LocalRenderer(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
}

void Raytracer::LocalRenderer::render(const Scene &scene)
{
    std::cout << "rendering from X: " << _start.x << " to " << _end.x << " and from Y:" << _start.y << " to " << _end.y << std::endl;
    for (unsigned x = _start.x; x < _end.x; x++) {
        for (unsigned y = _start.y; y < _end.y; y++) {
            sf::Vector3f colors{0, 0, 0};
            for (int i = 0; i < scene.getRaysPerPixel(); i++)
                colors += getPixelFColor(sf::Vector2f(x, y), scene);
            colors /= static_cast<float>(scene.getRaysPerPixel());
            addPixel({x, y}, colors);
        }
    }
    _nbFrames++;
}

void Raytracer::LocalRenderer::addPixel(sf::Vector2u pos, sf::Vector3f color)
{
    std::size_t widthX = _end.x - _start.x;
    std::size_t posInArray = (pos.y - _start.y) * widthX + (pos.x - _start.x);

    color *= 255.0f;
    color.x = std::min(color.x, 255.0f);
    color.y = std::min(color.y, 255.0f);
    color.z = std::min(color.z, 255.0f);
    if (_nbFrames != 0) {
        sf::Color old = _vertexArray[posInArray].color;
        sf::Vector3f oldColor = sf::Vector3f(old.r, old.g, old.b);
        if (oldColor == sf::Vector3f{0,0,0} || color == sf::Vector3f{0,0,0})
            color += oldColor;
        else {
            float weight = 1.0f / (_nbFrames + 1);
            color = oldColor * (1 - weight) + color * weight;
        }
    }
    _vertexArray[posInArray].position = sf::Vector2f(pos.x, pos.y);
    _vertexArray[posInArray].color = sf::Color(color.x, color.y, color.z);
}

sf::Vector3f Raytracer::LocalRenderer::getPixelFColor(sf::Vector2f pos, const Scene &scene)
{
    sf::Vector3f rayColor = sf::Vector3f(1, 1, 1);
    sf::Vector3f light = {0, 0, 0};
    std::size_t widthX = _end.x - _start.x;
    std::size_t widthY = _end.y - _start.y;
    Ray ray = Ray(scene.getCamera().getPos(),
                  scene.getCamera().getRot() + sf::Vector3f(pos.x / widthX - 0.5f, pos.y / widthY - 0.5f, 1));
    Object *old = nullptr;

    for (int bounces = 0; bounces <= scene.getNbBounces(); bounces++) {
        Object *obj = scene.getClosest(&ray, old);

        if (!obj)
            break;
        sf::Vector3f inter = obj->getIntersection(&ray);
        sf::Vector3f normal = obj->getNormal(inter);
        float strength = std::max(Math::dot(normal, -ray.getDir()), 0.0f);
        light += obj->getEmissionColor() * rayColor * strength * obj->getEmissionIntensity();
        rayColor *= obj->getColor();
        ray.setOrigin(inter);
        ray.reflect(normal, obj->getReflectivity());
        if (bounces == 0) {
            light += addSunLight(normal, inter, rayColor, scene, obj);
            addLightOfPoints(light, normal, inter, rayColor, scene, obj);// * (1.0f - obj->getReflectivity());
        }
        old = obj;
    }

    // Lumière ambiante
    light += rayColor * getAmbientLight(pos);
    return light;
}

void Raytracer::LocalRenderer::addLightOfPoints(sf::Vector3f &light, sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, const Scene &pool, Object *obj)
{
    for (auto &lightPoint : pool.getLightPoints()) {
        Ray ray(inter, Math::normalize(lightPoint.getPos() - inter));
        if (pool.getBetween(&ray, Math::length(lightPoint.getPos() - inter), obj, true) == nullptr) {
            sf::Vector3f test = std::max(Math::dot(normal, ray.getDir()), 0.0f) * color * lightPoint.getColorF();
            light += test;
        }
    }
}

sf::Vector3f Raytracer::LocalRenderer::addSunLight(sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, const Scene &pool, Object *obj)
{
    Ray ray(inter, -_sunLight);
    if (pool.getClosest(&ray, obj, true) != nullptr)
        return {0, 0, 0};
    return std::max(Math::dot(normal, -_sunLight), 0.0f) * color * _sunColor;
}

void Raytracer::LocalRenderer::setRange(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
}

void Raytracer::LocalRenderer::internalSetRange(sf::Vector2u start, sf::Vector2u end)
{
    _start = start;
    _end = end;

    std::size_t widthX = end.x - start.x;
    std::size_t widthY = end.y - start.y;
    std::size_t size = widthX * widthY;

    _vertexArray.clear();
    _vertexArray.setPrimitiveType(sf::Points);
    _vertexArray.resize(size);
    for (std::size_t x = 0; x < widthX; x++) {
        for (std::size_t y = 0; y < widthY; y++) {
            _vertexArray[y * widthX + x].position = sf::Vector2f(x, y);
            _vertexArray[y * widthX + x].color = sf::Color::Black;
        }
    }
}

int Raytracer::LocalRenderer::getThreadsCount() const
{
    return 1;
}

sf::VertexArray Raytracer::LocalRenderer::getVertexArray() const
{
    return _vertexArray;
}
