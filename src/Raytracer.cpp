/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Raytracer
*/

#include "Raytracer.hpp"
#include "scene/SceneBuilder.hpp"
#include "clusters/Client.hpp"
#include "clusters/NetworkRenderer.hpp"
#include "render/RendererPool.hpp"
#include "render/LocalRenderer.hpp"
#include <thread>
#include <algorithm>

Raytracer::Raytracer::Raytracer(int ac, char **av):
        _array({1, 1})
{
    // Client mode: ac == 2 and av[1] starts with "--port=
    if (ac == 2 && std::string(av[1]).find("--port=") == 0) {
        _isClient = true;
        std::string port = std::string(av[1]).substr(7);
        if (!std::ranges::all_of(port.begin(), port.end(), ::isdigit))
            throw std::invalid_argument("Port must be numeric");
        _port = static_cast<unsigned short>(std::stoul(port));
    }
    // Normal mode
    else {
        SceneBuilder builder(ac, av);

        _scene = builder.build();
        _isClient = false;
        _drawer = std::make_unique<Drawer>(_scene->getResolution().x, _scene->getResolution().y);

        auto renderer = std::make_unique<RendererPool>(sf::Vector2u{0, 0}, _scene->getResolution());
        // Create clusters
        if (!_scene->getClusters().empty()) {
            for (const auto &cluster : _scene->getClusters())
                renderer->addRenderer(std::make_unique<Clustering::NetworkRenderer>(cluster));
        }

        // Even if there are clusters, we still render the rest of the image on this computer
        std::size_t max = _scene->isMultithreadingEnabled() ? std::thread::hardware_concurrency() : 1;
        for (std::size_t i = 0; i < max; ++i)
            renderer->addRenderer(std::make_unique<LocalRenderer>(sf::Vector2u(0, 0), sf::Vector2u(1, 1)));

        // Set the range
        renderer->setRange();
        _array.resize(_scene->getResolution());
        _renderer = std::move(renderer);
    }
}

void Raytracer::Raytracer::run()
{
    if (!_isClient)
        runNormal();
    else
        runClient();
}

void Raytracer::Raytracer::runClient()
{
    Clustering::Client client(_port);

    client.run();
}

void Raytracer::Raytracer::runNormal()
{
    while (_drawer->isOpen()) {
        _renderer->render(*_scene, _array);
        _drawer->draw(_array);
        _drawer->saveToFile(_scene->getOutputFile());
    }
}
