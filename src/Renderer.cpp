/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "objects/Plane.hpp"
#include <numeric>
#define NB_THREADS 2

Renderer::Renderer()
{
    for (int i = 0; i < WINDOW_SIZE.x; i++)
        for (int j = 0; j < WINDOW_SIZE.y; j++)
            _vertexArray.append(sf::Vertex(sf::Vector2f(i, j), sf::Color::Black));
}

void Renderer::handleMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        _camera.move(Camera::FORWARD, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _camera.move(Camera::BACKWARD, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        _camera.move(Camera::LEFT, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _camera.move(Camera::RIGHT, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _camera.move(Camera::UP, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        _camera.move(Camera::DOWN, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _camera.turn(0, -0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _camera.turn(0, 0.1f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _camera.turn(-0.1f, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _camera.turn(0.1f, 0);
}

void Renderer::run(Scene *pool)
{
    _window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "RayTracer");
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            else
                handleMovement();
        }
        _window.clear();
//        perThread(0, WINDOW_SIZE.x, pool);
        std::vector<std::thread *> threads;
        for (int i = 0; i < NB_THREADS; i++) {
            threads.push_back(new std::thread(&Renderer::perThread, this, i * WINDOW_SIZE.x / NB_THREADS,
                                          (i + 1) * WINDOW_SIZE.x / NB_THREADS, pool));
        }
        for (int i = 0; i < NB_THREADS; i++) {
            threads[i]->join();
            delete threads[i];
        }
        draw();
        drawToFile();
        _window.display();
    }
}

void Renderer::perThread(int startX, int endX, Scene *pool)
{
    for (int x = startX; x < endX; x++) {
        for (int y = 0; y < WINDOW_SIZE.y; y++) {
            sf::Vector3f colors = sf::Vector3f(0, 0, 0);
            for (float i = 0; i < RAYS_PER_PIXEL; i++)
                colors += getPixelFColor(sf::Vector2f(x, y), pool);
            colors /= RAYS_PER_PIXEL;
            addPixel(sf::Vector2f(x, y), colors);
        }
    }
}

sf::Vector3f Renderer::getPixelFColor(sf::Vector2f pos, const Scene *pool)
{
    sf::Vector3f rayColor = sf::Vector3f(1, 1, 1);
    sf::Vector3f light = NULL_VEC_3;
    Ray ray = Ray(_camera.getPos(), _camera.getRot() +
    sf::Vector3f(pos.x / WINDOW_SIZE.x - 0.5f, pos.y / WINDOW_SIZE.y - 0.5f, 1));
    Object *old = nullptr;

    for (int bounces = 0; bounces <= NB_BOUNCE; bounces++) {
        Object *obj = pool->getClosest(&ray, old);

        if (!obj)
            break;
        sf::Vector3f inter = obj->getIntersection(&ray);
        sf::Vector3f normal = obj->getNormal(inter);
        float strength = std::max(Math::dot(normal, -ray.getDir()), 0.0f);

        light += obj->getEmissionColor() * rayColor * strength * obj->getEmissionIntensity();
        rayColor *= obj->getColor();

        // Bounc ray
        ray.setOrigin(inter);
        ray.reflect(normal);

        // Apply ambient light
        if (bounces == 0)
            light += addSunLight(normal, inter, rayColor, pool, obj);
        old = obj;
    }

    // Lumière ambiante
    light += rayColor * getAmbientLight(pos);
    return light;
}

sf::Vector3f Renderer::addSunLight(sf::Vector3f normal, sf::Vector3f inter, sf::Vector3f color, const Scene *pool, Object *obj)
{
    Ray ray(inter, -_sunLight);
    if (pool->getClosest(&ray, obj, true) != nullptr)
        return NULL_VEC_3;
    return std::max(Math::dot(normal, -_sunLight), 0.0f) * color * _sunColor;
}

void Renderer::addPixel(sf::Vector2f pos, sf::Vector3f color)
{
    color *= 255.0f;
    color.x = std::min(color.x, 255.0f);
    color.y = std::min(color.y, 255.0f);
    color.z = std::min(color.z, 255.0f);
    if (_nbFrames != 0) {
        sf::Color old = _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].color;
        sf::Vector3f oldColor = sf::Vector3f(old.r, old.g, old.b);
        if (oldColor == NULL_VEC_3 || color == NULL_VEC_3)
            color += oldColor;
        else {
            float weight = 1.0f / (_nbFrames + 1);
            color = oldColor * (1 - weight) + color * weight;
        }
    }
    _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].position = sf::Vector2f(pos.x, pos.y);
    _vertexArray[pos.y * WINDOW_SIZE.x + pos.x].color = sf::Color(color.x, color.y, color.z);
}
